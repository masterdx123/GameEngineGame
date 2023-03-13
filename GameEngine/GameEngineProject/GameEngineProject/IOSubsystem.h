#pragma once

#include "Common.h"
#include "Subsystem.h"
#include "IOComponent.h"

class IOSubsystem : public Subsystem
{
public:
	IOSubsystem(EventQueue* eQ_, std::vector<GameObject*>* gameObjects_) : Subsystem(SubsystemType::IO, eQ_, gameObjects_) {
		components = new std::vector<IOComponent>;

	};

	Component* AddComponent(Component* component_);
	void RemoveComponent(int i_) { components->erase(components->begin() + i_); }
	Component* GetComponent(int i_) { return &(components->at(i_)); }

	void Update();
	int GetNumComponents() { return components->size(); }

private:
	std::vector<IOComponent>* components;
};
