#pragma once

#include "Component.h"

class CircleColl2D : public Component {
public:
	CircleColl2D(GameObject* myObject_, Subsystem* mySystem_) : Component(ComponentType::CircleColl2D, myObject_, mySystem_) {};
	CircleColl2D(const CircleColl2D& other) : Component(ComponentType::CircleColl2D, other.myObject, other.mySystem) {};
	
	~CircleColl2D() {};
	CircleColl2D& operator=(const CircleColl2D& other);

	void Update() {};
};
