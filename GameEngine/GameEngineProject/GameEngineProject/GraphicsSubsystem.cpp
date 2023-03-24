#include "GraphicsSubsystem.h"
#include "EventQueue.h"


Component* GraphicsSubsystem::AddComponent(Component* component_)
{
	if (component_->GetType() == ComponentType::BoxShape2D)
	{
		BoxShape2D* temp = static_cast<BoxShape2D*>(component_);
		components->push_back(*temp);
		return &(components->back());
	}
	else
	{
		std::cout << "Tried to push a non-boxShape2D component to the graphics subsystem" << std::endl;
		return nullptr;
	}
}

void GraphicsSubsystem::Update()
{
	Render();
}
                     
void GraphicsSubsystem::Render()
{
	window->clear(sf::Color::Cyan);	

	//go through all graphics components and update them
	for (auto component : *components) {

		component.Update();
	}
	window->display();

	int eQsize = eventQueue->events.size();

	if (eQsize > 0)
	{
		Event* temp;

		for (int i = 0; i < eQsize; i++)
		{
			/* If there's an event, we check it out, and see if it's
			 * something this subsystem cares about (== type).
			 */

			temp = eventQueue->events[i];

			for (int j = 0; j < temp->systems.size(); j++)
			{
				if (temp->systems[j] == type)
				{
					/* If we care about it, we know we'll have a function
					 * to deal with it somewhere in the eventQueue.
					 */

					auto it = eventQueue->functionMap.find(type);

					auto it2 = it->second->find(temp->type);

					/* We find our function and pass in the event as its
					 * parameter. We then pop our subsystem off the event's
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

