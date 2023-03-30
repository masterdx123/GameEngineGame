#pragma once

#include "GameObject.h"
#include "EventQueue.h"
#include "GameplaySubsystem.h"



GameplayComponent::GameplayComponent(const GameplayComponent& other) : Component(other.type, other.myObject, other.mySystem)
{
	
	behaviours = new std::vector<Behaviour*>;

	for (int i = 0; i < other.behaviours->size(); i++)
	{
		behaviours->push_back(other.behaviours->at(i));
	}

	isShot = other.isShot;

	inRange = other.inRange;
	behaviourMap = other.behaviourMap;
	currentBehaviour = other.currentBehaviour;
	count = other.count;
	dir = other.dir;
	movingLeft = other.movingLeft;
	speed = other.speed;
	newWaypoint = other.newWaypoint;
	waypoints = other.waypoints;
}

GameplayComponent& GameplayComponent::operator=(const GameplayComponent& other)
{
	if (this == &other)
	{
		return *this;
	}

	memcpy(this, &other, sizeof(other));
	return *this;
}

void GameplayComponent::Update()
{

	std::vector<GameObject*> objects;
	std::vector<SubsystemType> systems;
	Event* event = new Event();
	int i;
	
	if (myObject->GetName() == "Enemy")
	{
		if (inRange)
		{
			std::unordered_map<BehaviourType, Behaviour*>::const_iterator it = behaviourMap.find(BehaviourType::Hunt);

			for (i = 0; i < mySystem->GetGameObjects()->size(); i++)
			{
				objects.push_back(mySystem->GetGameObjects()->at(i));
			}
			systems.push_back(SubsystemType::Gameplay);
			event->assignObjects(objects);
			event->assignSystems(systems);
			event->assignType(EventType::Movement);
			mySystem->GetEventQueue()->events.push_back(event);

			std::cout << "in range" << std::endl;
		}
		else
		{
			std::unordered_map<BehaviourType, Behaviour*>::const_iterator it = behaviourMap.find(BehaviourType::Patrol);


			if (myObject->GetBody()->GetPosition().x > (GoToNextWaypoint().x - 0.1) && myObject->GetBody()->GetPosition().x < (GoToNextWaypoint().x + 0.1)
				&& myObject->GetBody()->GetPosition().y >(GoToNextWaypoint().y - 0.1) && myObject->GetBody()->GetPosition().y < (GoToNextWaypoint().y + 0.1))
			{

				if (newWaypoint + 1 < waypoints.size())
				{
					newWaypoint++;
				}
				else
				{
					newWaypoint = 0;
				}
			}


			myObject->GetBody()->SetLinearVelocity(speed * (b2Vec2(GoToNextWaypoint().x, GoToNextWaypoint().y)
				- b2Vec2(myObject->GetBody()->GetPosition().x, myObject->GetBody()->GetPosition().y)));



		}
	}	
	
	if (myObject->GetName() == "Bullet" && isShot)
	{
		myObject->GetBody()->SetLinearVelocity(shotDirection);			
	}
		


	
}

void GameplayComponent::AddBehaviour(BehaviourType type_, std::string myString_)
{
	Behaviour* temp = new Behaviour(type_, myString_);
	behaviours->push_back(temp);
	behaviourMap.insert({ type_, behaviours->back() });
}

void GameplayComponent::SetPatrol()
{
	for (int i = 0; i < behaviours->size(); i++)
	{
		if (behaviours->at(i)->getType() == BehaviourType::Patrol)
		{
			currentBehaviour = behaviours->at(i);
		}
	}
}