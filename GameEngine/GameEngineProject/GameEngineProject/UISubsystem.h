#pragma once

#include "Common.h"
#include "Subsystem.h"
#include "UIComponent.h"


//Set UI subsystem
class UISubsystem : public Subsystem
{
public:
	UISubsystem(EventQueue* eQ_, std::vector<GameObject*>* gameObjects_) : Subsystem(SubsystemType::UI, eQ_, gameObjects_) {
		components = new std::vector<UIComponent>;

	};

	Component* AddComponent(Component* component_);
	void RemoveComponent(int i_) { components->erase(components->begin() + i_); }
	Component* GetComponent(int i_) { return &(components->at(i_)); }

	void Update();
	int GetNumComponents() { return components->size(); }

private:
	std::vector<UIComponent>* components;
};
