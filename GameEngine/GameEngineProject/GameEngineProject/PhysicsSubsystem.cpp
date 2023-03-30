#include "PhysicsSubsystem.h"
#include "EventQueue.h"

Component* PhysicsSubsystem::AddComponent(Component* component_)
{
	//add physics component to vector of physicsComponents
	if (component_->GetType() == ComponentType::Physics)
	{
		PhysicsComponent * temp = static_cast<PhysicsComponent*>(component_);
		
		PhysicsComponent* temp1 = new PhysicsComponent(*temp);
		components->push_back(temp1);
		return (components->back());
	}
	else
	{
		std::cout << "Tried to push a non-physics component to the physics subsystem" << std::endl;
		return nullptr;
	}
}

//set game world
void PhysicsSubsystem::SetWorld()
{

	b2Vec2 gravity(0.0f, 0.0f);
	world = new b2World(gravity);

}

//set game time and others
void PhysicsSubsystem::TimeUpdate()
{
	timeStep = 1.0f / 120.0f;
	velocityIterations = 8;
	positionIterations = 3;	
}

void PhysicsSubsystem::Update()
{
	//update world
	world->Step(timeStep, velocityIterations, positionIterations);


	// update components bellonging to physics subsystem
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
			//check if there is an event that matches the type of this subsystem

			temp = eventQueue->events[i];

			for (int j = 0; j < temp->systems.size(); j++)
			{
				if (temp->systems[j] == type)
				{
					//if that happens find the function in the eventqueue corresponding to the event

					auto it = eventQueue->functionMap.find(type);

					auto it2 = it->second->find(temp->type);

					//pass the event as the parameter and pop this subsystem off the list of events

					it2->second(temp);

					temp->systems.erase(temp->systems.begin() + j);

					//if its the last remove event from event queue

					if (temp->systems.size() == 0 && eventQueue->events[i] != nullptr)
					{
						delete eventQueue->events[i];
					} 
				}
			}
		}
	}
}


