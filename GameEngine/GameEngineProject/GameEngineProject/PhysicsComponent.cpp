#include "PhysicsComponent.h"
#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include "PhysicsSubsystem.h"


PhysicsComponent& PhysicsComponent::operator=(const PhysicsComponent& other)
{
	if (this == &other)
	{
		return *this;
	}

	memcpy(this, &other, sizeof(other));
	return *this;
}


void PhysicsComponent::SetCollisionShape()
{
	// create body def, fixture and set box for the object and apply everything to the body
	scalingFactor = 200.0f;	
	
	
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = *myObject->GetBodyPos().back();
	bodyDef.fixedRotation = true;

	playerBox.SetAsBox(HalfWidth, HalfWidth);

	PhysicsSubsystem* temp = static_cast<PhysicsSubsystem*>(mySystem);

	body = temp->GetWorld()->CreateBody(&bodyDef);

	myObject->SetBody(body);

	fixtureDef.shape = &playerBox;
	fixtureDef.density = 0.3f;
	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);
	
}


void PhysicsComponent::ChangeCoordinatesToGraphics()
{
	//change coordinates from physics position onto graphics position and send them to graphics component to update position
	sf::Vector2f playerGraphicsPosition;
	b2Vec2 playerPhysicsPosition = body->GetPosition();

	playerGraphicsPosition.x = (playerPhysicsPosition.x - HalfWidth) * scalingFactor;
	playerGraphicsPosition.y = (playerPhysicsPosition.y + HalfWidth) * scalingFactor * -1.0f;

	myObject->UpdatePosition(playerGraphicsPosition);
}



void PhysicsComponent::Update()
{
	if (body != nullptr)
	{
		// get object direction, normalize it and apply velocity to the body 
		b2Vec2 dir = myObject->GetDir();
		dir.Normalize();

		dir *= speed;

		body->SetLinearVelocity(dir);		
		 
		//call change coordinates to graphics 
		ChangeCoordinatesToGraphics();
	}
	else
	{
		std::cout << "There is no player" << std::endl;
	}

	//reset object direction
	myObject->ResetDir();
}
