#pragma once

#include "Component.h"

class UIComponent : public Component{
public:
	UIComponent(GameObject* myObject_, Subsystem* mySystem_) : Component(ComponentType::UI, myObject_, mySystem_) {};
	UIComponent(const UIComponent& other) : Component(other) {};

	UIComponent& operator=(const UIComponent& other);

	void Update();
};