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
		b2Vec2 dir = myObject->GetDir();
		dir.Normalize();

		dir *= speed;

		body->SetLinearVelocity(dir);		
		 
		ChangeCoordinatesToGraphics();
	}
	else
	{
		std::cout << "There is no player" << std::endl;
	}

	myObject->ResetDir();
}
