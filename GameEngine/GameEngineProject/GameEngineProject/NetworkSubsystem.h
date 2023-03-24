#pragma once

#include "Common.h"
#include "Subsystem.h"
#include "NetworkComponent.h"

class NetworkSubsystem : public Subsystem
{
public:
	NetworkSubsystem(EventQueue* eQ_, std::vector<GameObject*>* gameObjects_) : Subsystem(SubsystemType::Network, eQ_, gameObjects_) {
		components = new std::vector<NetworkComponent>;
	};

	Component* AddComponent(Component* component_);
	inline void RemoveComponent(int i_) { components->erase(components->begin() + i_); }
	inline Component* GetComponent(int i_) { return &(components->at(i_)); }

	void Update();
	inline int GetNumComponents() { return components->size(); }
private:
	std::vector<NetworkComponent>* components;
};
