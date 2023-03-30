#pragma once


#include "Component.h"
#include "Behaviour.h"
#include <Box2D/Box2D.h>
#include "GraphicsSubsystem.h"
#include "Vector2.h"


class GameplayComponent : public Component
{

public:
	GameplayComponent(GameObject* myObject_, Subsystem* mySystem_, std::vector<Vector2> waypoint_) : Component(ComponentType::Gameplay, myObject_, mySystem_), waypoints(waypoint_)
	{		
		bulletPos = b2Vec2(0, 0);

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

	GameplayComponent(const GameplayComponent& other);
	~GameplayComponent() { }
	GameplayComponent& operator=(const GameplayComponent& other);

	std::vector<Behaviour*>* GetBehaviours() { return behaviours; }
	Behaviour* GetCurrentBehaviour() { return currentBehaviour; }
	void SetCurrentBehaviour(Behaviour* behaviour_) { currentBehaviour = behaviour_; }

	void AddBehaviour(BehaviourType type_, std::string myString_);
	void RemoveBehaviour(int i_) { behaviours->erase(behaviours->begin() + i_); }

	inline int GetBehaviourCount() { if (behaviours != nullptr) return behaviours->size(); return -1; }

	void SetPatrol();
	Vector2 GoToNextWaypoint() { return waypoints[newWaypoint]; }

	void Update();

	inline void SetBulletPos(b2Vec2 playerPos_) 
	{
		bulletPos.Set(playerPos_.x, playerPos_.y);
	}
	inline void SetIsShot(bool isShot_) { isShot = isShot_; }
	inline void SetShotDirection()
	{
		

		
		hasBeenShot = true;

		b2Vec2 dir;
		float speed = 1;

		sf::Vector2i mousePos = sf::Mouse::getPosition(*GraphicsSubsystem::GetWindow());

		dir.x = mousePos.x - myObject->GetPosition().x;
		dir.y = (mousePos.y - myObject->GetPosition().y) * -1.0f;

		dir.Normalize();
		dir *= speed;
		shotDirection = dir;

		if (hasBeenShot)
			myObject->GetBody()->SetTransform(myObject->GetPlayerPos() + (b2Vec2(shotDirection.x * 0.25f, shotDirection.y * 0.25)), 0);
	}
	inline void SetInRange(bool inRange_) { inRange = inRange_; }

	bool isShot;
	b2Vec2 bulletPos;
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