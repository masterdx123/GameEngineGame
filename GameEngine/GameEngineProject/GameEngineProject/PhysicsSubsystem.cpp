#include "PhysicsSubsystem.h"
#include "EventQueue.h"

Component* PhysicsSubsystem::AddComponent(Component* component_)
{
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

void PhysicsSubsystem::SetWorld()
{

	b2Vec2 gravity(0.0f, 0.0f);
	world = new b2World(gravity);

}

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
			/* If there's an event, check it out, see if it's
			 * something this subsystem cares about (== type).
			 */

			temp = eventQueue->events[i];

			for (int j = 0; j < temp->systems.size(); j++)
			{
				if (temp->systems[j] == type)
				{
					/* If it cares about it, find the function 
					 * that handles it in the eventQueue.
					 */

					auto it = eventQueue->functionMap.find(type);

					auto it2 = it->second->find(temp->type);

					/* Find the function and pass in the event as its
					 * parameter. Then pop our subsystem off the event's
					 * subsystem list, so we don't react to it twice!
					 */

					it2->second(temp);

					temp->systems.erase(temp->systems.begin() + j);

					/* If we were the last subsystem to react to the event,
					 * we remove it from the event queue entirely, to save
					 * memory.
					 */

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


