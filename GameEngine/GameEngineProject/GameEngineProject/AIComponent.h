#pragma once


#include "Common.h"
#include "Component.h"
#include "Behaviour.h"
#include <Box2D/Box2D.h>


class AIComponent : public Component
{
public:
	AIComponent(GameObject* myObject_, Subsystem* mySystem_, Vector2 waypoint_) : Component(ComponentType::AI, myObject_, mySystem_)
	{
		currentBehaviour = nullptr; behaviours = new std::vector<Behaviour*>; inRange = false;
		count = 0;
		dir = -1;
		movingLeft = true;
		speed = 2.0f;
		waypoints.push_back(waypoint_);
	};

	AIComponent(const AIComponent& other);

	AIComponent& operator=(const AIComponent& other);

	std::vector<Behaviour*>* GetBehaviours() { return behaviours; }
	Behaviour* GetCurrentBehaviour() { return currentBehaviour; }
	void SetCurrentBehaviour(Behaviour* behaviour_) { currentBehaviour = behaviour_; }

	void AddBehaviour(BehaviourType type_, std::string myString_);
	void RemoveBehaviour(int i_) { behaviours->erase(behaviours->begin() + i_); }

	inline int GetBehaviourCount() { if (behaviours != nullptr) return behaviours->size(); return -1; }

	void SetPatrol();
	void ChangeCoordinatesToGraphics();

	void Update();

	inline void SetInRange(bool inRange_) { inRange = inRange_; }

private:
	std::vector<Behaviour*>* behaviours;
	std::unordered_map<BehaviourType, Behaviour*> behaviourMap;
	Behaviour* currentBehaviour;
	bool inRange;
	bool movingLeft;
	int count;
	int dir;
	float speed;
	std::vector<Vector2> waypoints;
};