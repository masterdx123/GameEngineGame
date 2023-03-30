#pragma once
#include "Common.h"
#include "SFML/Graphics.hpp"
#include "Vector2.h" 
#include "Subsystem.h"
#include "BoxShape2D.h"

//Set Graphics subsystem
class GraphicsSubsystem : public Subsystem {
public:
	GraphicsSubsystem(EventQueue* eventQueue_, std::vector<GameObject*>* gameObjects_) : Subsystem(SubsystemType::Graphics, eventQueue_, gameObjects_) {
		components = new std::vector<BoxShape2D>;

		//create game window
		window = new sf::RenderWindow(sf::VideoMode(800, 800), "Game Window");
	};

	~GraphicsSubsystem() { delete window; delete components; };

	Component* AddComponent(Component* component_);
	void RemoveComponent(int i_) { components->erase(components->begin() + i_); }
	Component* GetComponent(int i_) { return &(components->at(i_)); }

	static sf::RenderWindow* GetWindow() { return window; }

	void Update();
	int GetNumComponents() { return components->size(); }

	void Render();

private:
	std::vector<BoxShape2D>* components;
	static sf::RenderWindow* window;
	
};