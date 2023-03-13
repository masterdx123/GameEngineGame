#pragma once
#include "Common.h"

class EventQueue;
class GameObject;
class Component;

class Subsystem {
public: 
	Subsystem(SubsystemType type_, EventQueue* eventQueue_, std::vector<GameObject*>* gameObjects_) : type(type_), eventQueue(eventQueue_), gameObjects(gameObjects_) {};
	Subsystem(const Subsystem& other) : type(other.type), eventQueue(other.eventQueue), gameObjects(other.gameObjects) {};
	~Subsystem() {};

	SubsystemType GetType() { return type; }
	EventQueue* GetEventQueue() { return eventQueue; }
	std::vector<GameObject*>* GetGameObjects() { return gameObjects; }

	virtual void Update() = 0;
	virtual Component* AddComponent(Component* component_) = 0;
	virtual int GetNumComponents() = 0;

protected:
	const SubsystemType type;
	EventQueue* eventQueue;
	std::vector<GameObject*>* gameObjects;
};