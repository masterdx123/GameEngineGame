#pragma once

#include "AISubsystem.h"
#include "EventQueue.h"

Component* AISubsystem::AddComponent(Component* component_)
{
	if (component_->GetType() == ComponentType::AI)
	{
		AIComponent* temp = static_cast<AIComponent*>(component_);
		components->push_back(temp);
		return (components->back());
	}
	/*
	* else if (component_->GetType() == ComponentType::Bullet)
	{
		BulletComponent* temp = static_cast<BulletComponent*>(component_);
		component->push_back(*temp);
		return &(components->back());
	}
	*/
	
	else
	{
		std::cout << "Tried to push a non-AI component to the AI subsystem wot" << std::endl;
		return nullptr;
	}
}

void AISubsystem::Update()
{

	// update components bellonging to AI subsystem
	for (int i = 0; i < components->size(); i++)
	{
		components->at(i)->Update();
	}

	int eQsize = eventQueue->events.size();

	if (eQsize > 0)
	{
		Event* temp;

		for (int i = 0; i < eQsize; i++)
		{


			temp = eventQueue->events[i];

			for (int j = 0; j < temp->systems.size(); j++)
			{
				if (temp->systems[j] == type)
				{


					auto it = eventQueue->functionMap.find(type);

					auto it2 = it->second->find(temp->type);



					it2->second(temp);

					temp->systems.erase(temp->systems.begin() + j);



					if (temp->systems.size() == 0 && eventQueue->events[i] != nullptr)
					{
						delete eventQueue->events[i];
						//eventQueue->events.erase(eventQueue->events.begin() + i);
					}
				}
			}
		}
	}
}
