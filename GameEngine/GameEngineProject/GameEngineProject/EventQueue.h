#pragma once
#include "GameEngine.h"
#include "Event.h"

class EventQueue {
public:
	EventQueue() { InitialiseFunctionMaps(); }
	~EventQueue() {};
	std::vector<Event*> events;

	void InitialiseFunctionMaps();
	void deleteEvents(Event* event_);
	
	std::unordered_map<SubsystemType, std::unordered_map<EventType, void(*)(Event*)>*> functionMap;
	std::vector< std::unordered_map<EventType, void(*)(Event*)>*> functionMaps;
};