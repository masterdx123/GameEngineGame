#pragma once

#include "Component.h"
#include <Box2D/Box2D.h>

class PhysicsComponent : public Component {
public:
	PhysicsComponent(GameObject* myObject_, Subsystem* mySystem_, float HalfWidth_) : Component(ComponentType::Physics, myObject_, mySystem_) {
		speed = 0.2f;
		HalfWidth = HalfWidth_;
		SetCollisionShape();
		
	};
	PhysicsComponent(const PhysicsComponent& other) : Component(ComponentType::Physics, other.myObject, other.mySystem) {
		body = other.body;
		HalfWidth = other.HalfWidth;
		scalingFactor = other.scalingFactor;
		fixtureDef = other.fixtureDef;
		playerBox = other.playerBox;
		bodyDef= other.bodyDef;
		speed = other.speed;
	
	};

	~PhysicsComponent() {};
	PhysicsComponent& operator=(const PhysicsComponent& other);

	
	void SetCollisionShape();
	void ChangeCoordinatesToGraphics();

	inline void SetSpeed(float speed_) { speed = speed_; }
	inline float GetSpeed() { return speed; }
	

	void Update();
protected:
	float HalfWidth;
	float scalingFactor;
	b2FixtureDef fixtureDef;
	b2PolygonShape playerBox;
	b2Body* body;
	b2BodyDef bodyDef;
	

	float speed;
};