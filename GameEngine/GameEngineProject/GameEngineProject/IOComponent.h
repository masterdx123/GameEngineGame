#pragma once

#include "Common.h"
#include "Component.h"

/*
 * The IOComponent demonstrates how a subsystem can create events in response to
 * some trigger condition. The implementation is ugly (yours should be prettier)
 * but that's mainly so you can see transparently what's happening in the population
 * of our event data. Check it out in the Update() method.
 */

class IOComponent : public Component
{
public:
	inline IOComponent(GameObject* myObject_, Subsystem* mySystem_) : Component(ComponentType::IO, myObject_, mySystem_) {};
	inline IOComponent(const IOComponent& other) : Component(other) {};

	IOComponent& operator=(const IOComponent& other);

	void Update();

private:
	/* This is where you stick data unique to the IO component! */
};