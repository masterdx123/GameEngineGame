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

	Component* addComponent(Component* component_);
	inline void removeComponent(int i_) { components->erase(components->begin() + i_); }
	inline Component* getComponent(int i_) { return &(components->at(i_)); }

	void Update();
	inline int getNumComponents() { return components->size(); }

private:
	std::vector<IOComponent>* components;
};
