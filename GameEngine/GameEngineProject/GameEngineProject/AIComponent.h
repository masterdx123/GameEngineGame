#pragma once


#include "Component.h"
#include "Behaviour.h"
#include <Box2D/Box2D.h>
#include "GraphicsSubsystem.h"
#include "Vector2.h"


class AIComponent : public Component
{
public:
	AIComponent(GameObject* myObject_, Subsystem* mySystem_, std::vector<Vector2> waypoint_) : Component(ComponentType::AI, myObject_, mySystem_), waypoints(waypoint_)
	{		
		

		currentBehaviour = nullptr; behaviours = new std::vector<Behaviour*>; inRange = false; isShot = false;
		count = 0;
		dir = -1.0f;
		movingLeft = true;
		speed = 0.05f;

		if (waypoints.size() == 0)
		{
			waypoints = { Vector2(0.0f,0.0f) };
		}
		newWaypoint = 0;
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
	Vector2 GoToNextWaypoint() { return waypoints[newWaypoint]; }

	void Update();

	inline void SetIsShot(bool isShot_) { isShot = isShot_; }
	inline void SetShotDirection()
	{
		if (hasBeenShot)
			return;

		
		hasBeenShot = true;

		b2Vec2 dir;
		float speed = 1;

		sf::Vector2i mousePos = sf::Mouse::getPosition(*GraphicsSubsystem::GetWindow());

		dir.x = mousePos.x - myObject->GetPosition().x;
		dir.y = (mousePos.y - myObject->GetPosition().y) * -1.0f;

		dir.Normalize();
		dir *= speed;
		shotDirection = dir;
	}
	inline void SetInRange(bool inRange_) { inRange = inRange_; }

	bool isShot;
private:
	std::vector<Behaviour*>* behaviours;
	std::unordered_map<BehaviourType, Behaviour*> behaviourMap;
	Behaviour* currentBehaviour;
	bool inRange;
	bool movingLeft;
	int count;
	float dir;
	float speed;
	std::vector<Vector2> waypoints;
	int newWaypoint;
	bool hasBeenShot = false;
	b2Vec2 shotDirection = b2Vec2(0,0);

	
	
};