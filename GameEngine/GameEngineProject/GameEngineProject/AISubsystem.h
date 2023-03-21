#pragma once


#include "Common.h"
#include "Subsystem.h"
#include "AIComponent.h"

class AISubsystem : public Subsystem
{
public:
	AISubsystem(EventQueue* eQ_, std::vector<GameObject*>* gameObjects_) : Subsystem(SubsystemType::AI, eQ_, gameObjects_) {
		components = new std::vector<AIComponent>;
	};

	Component* AddComponent(Component* component_);
	inline void RemoveComponent(int i_) { components->erase(components->begin() + i_); }
	inline Component* GetComponent(int i_) { return &(components->at(i_)); }

	void Update();
	inline int GetNumComponents() { return components->size(); }
private:
	std::vector<AIComponent>* components;
};