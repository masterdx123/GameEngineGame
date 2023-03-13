#include "EventQueue.h"
#include "GameObject.h"


void PhysicsMoveUp(Event* event_)
{
	event_->objects[0]->GetPlayerShape()->move(0,1);
}

void PhysicsMoveDown(Event* event_)
{
	event_->objects[0]->GetPlayerShape()->move(0, -1);
}

void PhysicsMoveLeft(Event* event_)
{
	event_->objects[0]->GetPlayerShape()->move(-1, 0);
}

void PhysicsMoveRight(Event* event_)
{
	event_->objects[0]->GetPlayerShape()->move(1, 0);
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


