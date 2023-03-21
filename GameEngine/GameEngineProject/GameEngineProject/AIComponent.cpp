#pragma once

#include "AIComponent.h"
#include "GameObject.h"
#include "EventQueue.h"
#include "AISubsystem.h"

AIComponent::AIComponent(const AIComponent& other) : Component(other.type, other.myObject, other.mySystem)
{
	behaviours = new std::vector<Behaviour*>;

	for (int i = 0; i < other.behaviours->size(); i++)
	{
		behaviours->push_back(other.behaviours->at(i));
	}

	inRange = other.inRange;
	behaviourMap = other.behaviourMap;
	currentBehaviour = other.currentBehaviour;
	count = other.count;
	dir = other.dir;
	movingLeft = other.movingLeft;
	speed = other.speed;
}

AIComponent& AIComponent::operator=(const AIComponent& other)
{
	if (this == &other)
	{
		return *this;
	}

	memcpy(this, &other, sizeof(other));
	return *this;
}

void AIComponent::Update()
{
	std::vector<GameObject*> objects;
	std::vector<SubsystemType> systems;
	Event* event = new Event();
	int i;
	

	if (inRange)
	{
		std::unordered_map<BehaviourType, Behaviour*>::const_iterator it = behaviourMap.find(BehaviourType::Hunt);

		for (i = 0; i < mySystem->GetGameObjects()->size(); i++)
		{
			objects.push_back(mySystem->GetGameObjects()->at(i));
		}
		systems.push_back(SubsystemType::AI);
		event->assignObjects(objects);
		event->assignSystems(systems);
		event->assignType(EventType::Movement);
		mySystem->GetEventQueue()->events.push_back(event);

		std::cout << "in range" << std::endl;
	}
	else
	{
		std::cout << "patrolling" << std::endl;
		std::unordered_map<BehaviourType, Behaviour*>::const_iterator it = behaviourMap.find(BehaviourType::Patrol);

		for (i = 0; i < mySystem->GetGameObjects()->size(); i++)
		{
			objects.push_back(mySystem->GetGameObjects()->at(i));
		}
		systems.push_back(SubsystemType::AI);
		event->assignObjects(objects);
		event->assignSystems(systems);
		event->assignType(EventType::Movement);
		mySystem->GetEventQueue()->events.push_back(event);
		
		
		

		ChangeCoordinatesToGraphics();

		
	}
}

void AIComponent::AddBehaviour(BehaviourType type_, std::string myString_)
{
	Behaviour* temp = new Behaviour(type_, myString_);
	behaviours->push_back(temp);
	behaviourMap.insert({ type_, behaviours->back() });
}

void AIComponent::SetPatrol()
{
	for (int i = 0; i < behaviours->size(); i++)
	{
		if (behaviours->at(i)->getType() == BehaviourType::Patrol)
		{
			currentBehaviour = behaviours->at(i);
		}
	}
}

void AIComponent::ChangeCoordinatesToGraphics()
{

	myObject->GetBody()->SetLinearVelocity(b2Vec2((myObject->GetBody()->GetLinearVelocity().x + speed)*dir, (myObject->GetBody()->GetLinearVelocity().y + speed)*dir));

	std::cout << ""<< myObject->GetBody()->GetPosition().x << std::endl;
	std::cout << "" << myObject->GetBody()->GetPosition().y << std::endl;

	if (movingLeft == true)
	{
		if (dir == -1 && count >= 3)
		{
			dir = -dir;
			count = 0;
			movingLeft = false;
		}
		if (dir == -1)
		{
			count++;
		}
	}
	else if (movingLeft==false)
	{
		if (dir == 1 && count >= 3)
		{
			dir = -dir;
			count = 0;
			movingLeft = true;
		}
		if (dir == 1)
		{
			count++;
		}
	}

	myObject->UpdatePosition(myObject->GetPosition());

	
	
	
}