#include "GraphicsSubsystem.h"
#include "EventQueue.h"

sf::RenderWindow* GraphicsSubsystem::window;

Component* GraphicsSubsystem::AddComponent(Component* component_)
{
	//add graphics component to vector of graphics components
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
	//make window cyan color
	window->clear(sf::Color::Cyan);	

	//go through all graphics components and update them
	for (auto component : *components) {

		component.Update();
	}

	//display window
	window->display();

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

