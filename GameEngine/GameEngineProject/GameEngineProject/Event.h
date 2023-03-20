#pragma once

#include "Common.h"

class GameObject;

class Event {
public:
	Event(EventType type_, std::vector<GameObject*> objects_, std::vector<SubsystemType> systems_) : type(type_), objects(objects_), systems(systems_) {};

	Event() { type = EventType::Unassigned; }

	~Event() {
		std::cout << "I'm an event and I'm being deleted!" << std::endl;
	}

	Event(const Event& other) : type(other.type), objects(other.objects), systems(other.systems) {};

	Event& operator=(const Event& other) { if (this == &other) return *this; Event a(other.type, other.objects, other.systems); return a; };

	void assignType(EventType type_) { type = type_; }
	void assignObjects(std::vector<GameObject*> objects_) { objects = objects_; }
	void assignSystems(std::vector<SubsystemType> systems_) { systems = systems_; }

	EventType type;
	std::vector<GameObject*> objects;
	std::vector<SubsystemType> systems;
};
