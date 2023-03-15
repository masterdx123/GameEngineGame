#include "EventQueue.h"
#include "GameObject.h"


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


void EventQueue::InitialiseFunctionMaps()
{
	std::unordered_map<EventType, void(*)(Event*)>* movementMap = new std::unordered_map<EventType, void(*)(Event*)>;

	movementMap->insert({ EventType::MoveUp, &PhysicsMoveUp });
	movementMap->insert({ EventType::MoveLeft, &PhysicsMoveLeft });
	movementMap->insert({ EventType::MoveDown, &PhysicsMoveDown });
	movementMap->insert({ EventType::MoveRight, &PhysicsMoveRight });

	functionMaps.push_back(movementMap);
	functionMap.insert({ SubsystemType::Physics, movementMap });
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


