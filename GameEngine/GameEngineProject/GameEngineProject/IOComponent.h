#pragma once

#include "Component.h"

class IOComponent : public Component{
public:
	IOComponent(GameObject* myObject_, Subsystem* mySystem_) : Component(ComponentType::IO, myObject_, mySystem_) {};
	IOComponent(const IOComponent& other) : Component(other) {};

	IOComponent& operator=(const IOComponent& other);

	void Update();
};