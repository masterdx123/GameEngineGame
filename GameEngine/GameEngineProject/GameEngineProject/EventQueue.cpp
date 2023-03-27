#include "EventQueue.h"
#include "GameObject.h"
#include "AIComponent.h"



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

//void EnemyMoveUp(Event* event_) {
//
//	b2Vec2 temp = event_->objects[1]->GetDir();
//	temp.y += 1.0f;
//
//
//	event_->objects[1]->SetDir(temp);
//}
//void EnemyMoveDown(Event* event_) {
//
//	b2Vec2 temp = event_->objects[1]->GetDir();
//	temp.y -= 1.0f;
//
//
//	event_->objects[1]->SetDir(temp);
//}
//void EnemyMoveLeft(Event* event_) {
//
//	b2Vec2 temp = event_->objects[1]->GetDir();
//	temp.y -= 1.0f;
//
//
//	event_->objects[1]->SetDir(temp);
//}
//void EnemyMoveRight(Event* event_) {
//	b2Vec2 temp = event_->objects[1]->GetDir();
//	temp.y += 1.0f;
//
//
//	event_->objects[1]->SetDir(temp);
//}

void AIMovement(Event* event_)
{
	for (int i = 0; i < event_->objects.size(); i++)
	{
		GameObject* temp = event_->objects[i];

		if (temp->GetName() != "Player")
		{
			Component* ptr = temp->GetComponent(ComponentType::AI);
			AIComponent* tempAI = static_cast<AIComponent*>(ptr);
			tempAI->SetInRange(false);

			//handle speed and change body pos here
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

	functionMaps.push_back(movementMap);
	functionMap.insert({ SubsystemType::Physics, movementMap });

	/*std::unordered_map<EventType, void(*)(Event*)>* enemyMap = new std::unordered_map<EventType, void(*)(Event*)>;

	enemyMap->insert({ EventType::MoveUp, &EnemyMoveUp });
	enemyMap->insert({ EventType::MoveLeft, &EnemyMoveLeft });
	enemyMap->insert({ EventType::MoveDown, &EnemyMoveDown });
	enemyMap->insert({ EventType::MoveRight, &EnemyMoveRight });

	functionMaps.push_back(enemyMap);
	functionMap.insert({ SubsystemType::Physics, enemyMap });*/

	std::unordered_map<EventType, void(*)(Event*)>* aiMap = new std::unordered_map<EventType, void(*)(Event*)>;

	aiMap->insert({ EventType::Movement, &AIMovement });

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


