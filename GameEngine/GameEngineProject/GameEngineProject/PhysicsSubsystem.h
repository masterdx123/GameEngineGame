#pragma once
#include "Common.h"
#include "Subsystem.h"
#include "PhysicsComponent.h"

//Set Physics subsystem
class PhysicsSubsystem : public Subsystem {
public:
	PhysicsSubsystem(EventQueue* eventQueue_, std::vector<GameObject*>* gameObjects_) : Subsystem(SubsystemType::Physics, eventQueue_, gameObjects_) {
		components = new std::vector<Component*>;
		SetWorld();
		TimeUpdate();
		
		
	};
	~PhysicsSubsystem();

	Component* AddComponent(Component* component_);
	void RemoveComponent(int i_) { components->erase(components->begin() + i_); }
	Component* GetComponent(int i_) { return (components->at(i_)); }

	void Update();
	void SetWorld();
	void TimeUpdate();

	b2World* GetWorld() { return world; }
	
	int GetNumComponents() { return components->size(); }
private:
	std::vector<Component*>* components;
	b2World* world;
	float timeStep;
	int velocityIterations;
	int positionIterations;
};
