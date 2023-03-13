#pragma once
#include "Common.h"

class GameObject;
class Subsystem;


class Component {
public:
	Component(ComponentType type_, GameObject* myObject_, Subsystem* mySystem_) : type(type_), myObject(myObject_), mySystem(mySystem_) {};
	Component(const Component& other) : type(other.type), myObject(other.myObject), mySystem(other.mySystem) {};
	~Component() {};

	Component& operator=(const Component& other) {
		if (this == &other)
		{
			return *this;
		}

		memcpy(this, &other, sizeof(other));
		return *this;
	};

	const ComponentType GetType() { return type; }
	GameObject* GetMyObject() { return myObject; }
	Subsystem* GetMySystem() { return mySystem; }

	GameObject* ownerOfComponent = nullptr;
	virtual void Update() = 0;

protected:
	const ComponentType type;
	GameObject* myObject;
	Subsystem* mySystem;
};