#pragma once
#include "Common.h"
#include "Subsystem.h"
#include "BoxColl2D.h"
#include "CircleColl2D.h" 


class PhysicsSubsystem : public Subsystem {
public:
	PhysicsSubsystem(EventQueue* eventQueue_, std::vector<GameObject*>* gameObjects_) : Subsystem(SubsystemType::Physics, eventQueue_, gameObjects_) {
		components = new std::vector<Component*>;
	};
	~PhysicsSubsystem();

	Component* AddComponent(Component* component_);
	void RemoveComponent(int i_) { components->erase(components->begin() + i_); }
	Component* GetComponent(int i_) { return (components->at(i_)); }

	void Update();
	int GetNumComponents() { return components->size(); }
private:
	std::vector<Component*>* components;
};
