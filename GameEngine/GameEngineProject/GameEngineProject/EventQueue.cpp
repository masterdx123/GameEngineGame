#include "EventQueue.h"
#include "GameObject.h"
#include "GameplayComponent.h"
#include "BulletComponent.h"



void PhysicsMoveUp(Event* event_)
{
	b2Vec2 temp = event_->objects[0]->GetDir();
	temp.y += 1.0f;		


	event_->objects[0]->SetDir(temp);
}

void PhysicsMoveDown(Event* event_)
{
	
	b2Vec2 temp = event_->objects[0]->GetDir();
	temp.y -= 1.0f;		

	
	event_->objects[0]->SetDir(temp);
}

void PhysicsMoveLeft(Event* event_)
{
	
	b2Vec2 temp = event_->objects[0]->GetDir();
	temp.x -= 1.0f;		

	
	event_->objects[0]->SetDir(temp);
}

void PhysicsMoveRight(Event* event_)
{
	
	b2Vec2 temp = event_->objects[0]->GetDir();
	temp.x += 1.0f;		

	
	event_->objects[0]->SetDir(temp);
}

void PhysicsMovePlayer2(Event* event_) {

	for (int i = 0; i < event_->objects.size(); i++)
	{
		GameObject* temp = event_->objects[i];

		if (temp->GetName() == "Player2")
		{
			b2Vec2 datapos = event_->positionData;

			temp->GetBody()->SetTransform(datapos, 0);
		}
	}

}


void AIMovement(Event* event_)
{
	for (int i = 0; i < event_->objects.size(); i++)
	{
		GameObject* temp = event_->objects[i];

		if (temp->GetName() == "Enemy")
		{
			Component* ptr = temp->GetComponent(ComponentType::Gameplay);
			GameplayComponent* tempAI = static_cast<GameplayComponent*>(ptr);
			tempAI->SetInRange(false);

			//handle speed and change body pos here
		}
		
	}

}

void ShotEvent(Event* event_) {

	for (int i = 0; i < event_->objects.size(); i++)
	{
		GameObject* temp = event_->objects[i];
		b2Vec2 tempPos;
		if (temp->GetName() == "Player")
		{
			Component* ptr = temp->GetComponent(ComponentType::Gameplay);
			GameplayComponent* tempBullet = static_cast<GameplayComponent*>(ptr);
			tempPos = temp->GetBody()->GetPosition();
			
		}
		if (temp->GetName() == "Bullet")
		{
			Component* ptr = temp->GetComponent(ComponentType::Gameplay);
			GameplayComponent* tempBullet = static_cast<GameplayComponent*>(ptr);
			bool test1 = tempBullet->isShot;
			tempBullet->SetIsShot(true);
			tempBullet->SetShotDirection();
			temp->SetPlayerPos(tempPos);
		}
		
	}
}




void EventQueue::InitialiseFunctionMaps()
{
	std::unordered_map<EventType, void(*)(Event*)>* movementMap = new std::unordered_map<EventType, void(*)(Event*)>;

	movementMap->insert({ EventType::MoveUp, &PhysicsMoveUp }); 
	movementMap->insert({ EventType::MoveLeft, &PhysicsMoveLeft });
	movementMap->insert({ EventType::MoveDown, &PhysicsMoveDown });
	movementMap->insert({ EventType::MoveRight, &PhysicsMoveRight });
	movementMap->insert({ EventType::SetPosition, &PhysicsMovePlayer2 });

	functionMaps.push_back(movementMap);
	functionMap.insert({ SubsystemType::Physics, movementMap });

	

	std::unordered_map<EventType, void(*)(Event*)>* gameplayMap = new std::unordered_map<EventType, void(*)(Event*)>;

	gameplayMap->insert({ EventType::Movement, &AIMovement });
	gameplayMap->insert({ EventType::Shot, &ShotEvent });

	functionMaps.push_back(gameplayMap);
	functionMap.insert({ SubsystemType::Gameplay, gameplayMap });
}

void EventQueue::deleteEvents(Event* event_)
{
	for (int i = 0; i < events.size(); i++)
	{
		if (events[i] == event_)
		{
			delete events[i];
			events.erase(events.begin() + i);
		}
	}
}


