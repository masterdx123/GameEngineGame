#pragma once

#include "GameObject.h"
#include "EventQueue.h"
#include "GameplaySubsystem.h"


//copy constructor
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
		//keep the enemy patrolling until something gets in range
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

			//move enemy from waypoint coordinates from one to another repeatedly
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

			//set velocity of the enemy to move into the waypoint
			myObject->GetBody()->SetLinearVelocity(speed * (b2Vec2(GoToNextWaypoint().x, GoToNextWaypoint().y)
				- b2Vec2(myObject->GetBody()->GetPosition().x, myObject->GetBody()->GetPosition().y)));



		}
	}	
	

	if (myObject->GetName() == "Bullet" && isShot)
	{
		//set velocity of bullet to be the direction its shooting
		myObject->GetBody()->SetLinearVelocity(shotDirection);			
	}
		


	
}

//add a behaviour to the map
void GameplayComponent::AddBehaviour(BehaviourType type_, std::string myString_)
{
	Behaviour* temp = new Behaviour(type_, myString_);
	behaviours->push_back(temp);
	behaviourMap.insert({ type_, behaviours->back() });
}

//set the patrol state to be the current behaviour
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