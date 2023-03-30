#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include "UISubsystem.h"
#include "EventQueue.h"


UIComponent& UIComponent::operator=(const UIComponent& other)
{
	if (this == &other)
	{
		return *this;
	}

	memcpy(this, &other, sizeof(other));
	return *this;
}

void UIComponent::Update()
{
	std::vector<GameObject*> objects;
	std::vector<SubsystemType> systems;
	//Event* event; //= new Event();
	int i;
	//std::cout << myObject->GetClientIndex() << std::endl;
	/*if (myObject->GetClientIndex() == 0)
	{
		
	}*/
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		Event* event = new Event();

		for (i = 0; i < mySystem->GetGameObjects()->size(); i++)
		{
			objects.push_back(mySystem->GetGameObjects()->at(i));
		}
		systems.push_back(SubsystemType::Physics);
		event->assignObjects(objects);
		event->assignSystems(systems);
		event->assignType(EventType::MoveUp);
		mySystem->GetEventQueue()->events.push_back(event);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		Event* event = new Event();

		for (i = 0; i < mySystem->GetGameObjects()->size(); i++)
		{
			objects.push_back(mySystem->GetGameObjects()->at(i));
		}

		systems.push_back(SubsystemType::Physics);
		event->assignObjects(objects);
		event->assignSystems(systems);
		event->assignType(EventType::MoveLeft);
		mySystem->GetEventQueue()->events.push_back(event);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		Event* event = new Event();

		for (i = 0; i < mySystem->GetGameObjects()->size(); i++)
		{
			objects.push_back(mySystem->GetGameObjects()->at(i));
		}

		systems.push_back(SubsystemType::Physics);
		event->assignObjects(objects);
		event->assignSystems(systems);
		event->assignType(EventType::MoveDown);
		mySystem->GetEventQueue()->events.push_back(event);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		Event* event = new Event();

		for (i = 0; i < mySystem->GetGameObjects()->size(); i++)
		{
			objects.push_back(mySystem->GetGameObjects()->at(i));
		}

		systems.push_back(SubsystemType::Physics);
		event->assignObjects(objects);
		event->assignSystems(systems);
		event->assignType(EventType::MoveRight);
		mySystem->GetEventQueue()->events.push_back(event);

	}
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		Event* event = new Event();

		for (i = 0; i < mySystem->GetGameObjects()->size(); i++)
		{
			objects.push_back(mySystem->GetGameObjects()->at(i));
		}
		systems.push_back(SubsystemType::Gameplay);
		event->assignObjects(objects);
		event->assignSystems(systems);
		event->assignType(EventType::Shot);
		mySystem->GetEventQueue()->events.push_back(event);
	}
	
}