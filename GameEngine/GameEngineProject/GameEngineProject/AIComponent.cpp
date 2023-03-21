#pragma once

#include "AIComponent.h"
#include "GameObject.h"

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
	if (inRange)
	{
		std::unordered_map<BehaviourType, Behaviour*>::const_iterator it = behaviourMap.find(BehaviourType::Hunt);
		std::cout << "in range" << std::endl;
	}
	else
	{
		std::unordered_map<BehaviourType, Behaviour*>::const_iterator it = behaviourMap.find(BehaviourType::Patrol);

		sf::Vector2f enemyGraphicsPosition;

		enemyGraphicsPosition = myObject->GetPosition();

		b2Vec2 dir = myObject->GetDir();
		float speed = 2.f;

		dir *= speed;

		myObject->GetBody()->SetLinearVelocity(dir);

		myObject->UpdatePosition(enemyGraphicsPosition);
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