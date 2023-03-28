#include "EventQueue.h"
#include "GameObject.h"
#include "AIComponent.h"
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
			Component* ptr = temp->GetComponent(ComponentType::AI);
			AIComponent* tempAI = static_cast<AIComponent*>(ptr);
			tempAI->SetInRange(false);

			//handle speed and change body pos here
		}
		
	}

}

void ShotEvent(Event* event_) {

	for (int i = 0; i < event_->objects.size(); i++)
	{
		GameObject* temp = event_->objects[i];

		if (temp->GetName() == "Bullet")
		{
			Component* ptr = temp->GetComponent(ComponentType::AI);
			AIComponent* tempBullet = static_cast<AIComponent*>(ptr);
			bool test1 = tempBullet->isShot;
			tempBullet->SetIsShot(true);
			tempBullet->SetShotDirection();
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

	

	std::unordered_map<EventType, void(*)(Event*)>* aiMap = new std::unordered_map<EventType, void(*)(Event*)>;

	aiMap->insert({ EventType::Movement, &AIMovement });
	aiMap->insert({ EventType::Shot, &ShotEvent });

	functionMaps.push_back(aiMap);
	functionMap.insert({ SubsystemType::AI, aiMap });
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


