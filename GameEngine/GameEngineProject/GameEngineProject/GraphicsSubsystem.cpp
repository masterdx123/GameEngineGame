#include "GraphicsSubsystem.h"
#include "Common.h"
#include "BoxShape2D.h"
#include "GameObject.h"




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
	sf::Event e;

	window->pollEvent(e);

	if (e.type == sf::Event::Closed) {
		window->close();

	}
	if (e.type == sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		window->close();
	}
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
	
}

