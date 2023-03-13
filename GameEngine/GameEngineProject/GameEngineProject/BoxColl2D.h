#pragma once

#include "Component.h"

class BoxColl2D : public Component {
public:
	BoxColl2D(GameObject* myObject_, Subsystem* mySystem_) : Component(ComponentType::BoxColl2D, myObject_, mySystem_) {};
	BoxColl2D(const BoxColl2D& other) : Component(ComponentType::BoxColl2D, other.myObject, other.mySystem) {};

	~BoxColl2D() {};
	BoxColl2D& operator=(const BoxColl2D& other);

	void Update() {};
};