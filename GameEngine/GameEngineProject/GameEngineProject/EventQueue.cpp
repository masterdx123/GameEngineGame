#include "EventQueue.h"
#include "GameObject.h"


void PhysicsMoveUp(Event* event_)
{
	//std::cout << "A move up event occurred! It was applied to entity \"" << event_->objects[0]->GetName() << "\"" << std::endl;
	b2Vec2 temp = event_->objects[0]->GetDir();
	temp.y += 1.0f;		// repeat this for all events, with the x changing for left/right, y for up/down

//	event_->objects[0]->GetDir() = b2Vec2(0.0f, 1.0f);
	event_->objects[0]->SetDir(temp);
}

void PhysicsMoveDown(Event* event_)
{
	//std::cout << "A move down event occurred! It was applied to entity \"" << event_->objects[0]->GetName() << "\"" << std::endl;
	//event_->objects[0]->GetPlayerBody()->SetLinearVelocity(b2Vec2(0.0f, -1.0f));
	b2Vec2 temp = event_->objects[0]->GetDir();
	temp.y -= 1.0f;		// repeat this for all events, with the x changing for left/right, y for up/down

	//	event_->objects[0]->GetDir() = b2Vec2(0.0f, 1.0f);
	event_->objects[0]->SetDir(temp);
}

void PhysicsMoveLeft(Event* event_)
{
	//std::cout << "A move left event occurred! It was applied to entity \"" << event_->objects[0]->GetName() << "\"" << std::endl;
	//event_->objects[0]->GetPlayerBody()->SetLinearVelocity(b2Vec2(-1.0f, 0.0f));
	b2Vec2 temp = event_->objects[0]->GetDir();
	temp.x -= 1.0f;		// repeat this for all events, with the x changing for left/right, y for up/down

	//	event_->objects[0]->GetDir() = b2Vec2(0.0f, 1.0f);
	event_->objects[0]->SetDir(temp);
}

void PhysicsMoveRight(Event* event_)
{
	//std::cout << "A move right event occurred! It was applied to entity \"" << event_->objects[0]->GetName() << "\"" << std::endl;
	//event_->objects[0]->GetPlayerBody()->SetLinearVelocity(b2Vec2(1.0f, 0.0f));
	b2Vec2 temp = event_->objects[0]->GetDir();
	temp.x += 1.0f;		// repeat this for all events, with the x changing for left/right, y for up/down

	//	event_->objects[0]->GetDir() = b2Vec2(0.0f, 1.0f);
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


