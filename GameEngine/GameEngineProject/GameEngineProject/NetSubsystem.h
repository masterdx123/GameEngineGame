#pragma once
#include "Subsystem.h"
#include "NetComponent.h"


class NetSubsystem : public Subsystem
{
public:
	NetSubsystem(EventQueue* eQ_, std::vector<GameObject*>* gameObjects_) : Subsystem(SubsystemType::Network, eQ_, gameObjects_) {
		components = new std::vector<NetComponent>;
	};

	Component* AddComponent(Component* component_);
	inline void RemoveComponent(int i_) { components->erase(components->begin() + i_); }
	inline Component* GetComponent(int i_) { return &(components->at(i_)); }

	void Update();
	inline int GetNumComponents() { return components->size(); }
private:
	std::vector<NetComponent>* components;
};
