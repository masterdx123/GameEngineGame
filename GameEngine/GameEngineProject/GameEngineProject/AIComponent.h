#pragma once


#include "Common.h"
#include "Component.h"
#include "Behaviour.h"


class AIComponent : public Component
{
public:
	AIComponent(GameObject* myObject_, Subsystem* mySystem_) : Component(ComponentType::AI, myObject_, mySystem_)
	{
		currentBehaviour = nullptr; behaviours = new std::vector<Behaviour*>; inRange = false;
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

	void Update();

	inline void SetInRange(bool inRange_) { inRange = inRange_; }

private:
	std::vector<Behaviour*>* behaviours;
	std::unordered_map<BehaviourType, Behaviour*> behaviourMap;
	Behaviour* currentBehaviour;
	bool inRange;
};