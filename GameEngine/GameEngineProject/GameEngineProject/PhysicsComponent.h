#pragma once

#include "Component.h"
#include <Box2D/Box2D.h>

class PhysicsComponent : public Component {
public:
	PhysicsComponent(GameObject* myObject_, Subsystem* mySystem_) : Component(ComponentType::Physics, myObject_, mySystem_) {	
		SetCollisionShape();
		speed = 0.2f;
	};
	PhysicsComponent(const PhysicsComponent& other) : Component(ComponentType::Physics, other.myObject, other.mySystem) {
		player = other.player;
		playerHalfWidth = other.playerHalfWidth;
		scalingFactor = other.scalingFactor;
		fixtureDef = other.fixtureDef;
		playerBD = other.playerBD;
		playerBox = other.playerBox;
		speed = other.speed;
	
	};

	~PhysicsComponent() {};
	PhysicsComponent& operator=(const PhysicsComponent& other);

	
	void SetCollisionShape();
	void CreateBodyDef();
	void SetFixture();
	void ChangeCoordinatesToGraphics();

	inline void SetSpeed(float speed_) { speed = speed_; }
	inline float GetSpeed() { return speed; }
	

	void Update();
protected:
	float playerHalfWidth;
	float scalingFactor;

	b2FixtureDef fixtureDef;
	b2BodyDef playerBD;
	
	b2PolygonShape playerBox;
	b2Body* player;

	float speed;
};