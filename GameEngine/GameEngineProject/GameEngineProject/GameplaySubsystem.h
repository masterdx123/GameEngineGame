#pragma once


#include "Common.h"
#include "Subsystem.h"
#include "GameplayComponent.h"

//Set Gameplay subsystem
class GameplaySubsystem : public Subsystem
{
public:
	GameplaySubsystem(EventQueue* eQ_, std::vector<GameObject*>* gameObjects_) : Subsystem(SubsystemType::Gameplay, eQ_, gameObjects_) {
		components = new std::vector<GameplayComponent*>;
	};

	Component* AddComponent(Component* component_);
	inline void RemoveComponent(int i_) { components->erase(components->begin() + i_); }
	inline Component* GetComponent(int i_) { return (components->at(i_)); }

	void Update();
	inline int GetNumComponents() { return components->size(); }
private:
	std::vector<GameplayComponent*>* components;
};