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
	playerHalfWidth = 0.5f;

	
	playerBox.SetAsBox(playerHalfWidth, playerHalfWidth);

	CreateBodyDef();
}

void PhysicsComponent::CreateBodyDef()
{
	b2BodyDef playerBD;
	playerBD.type = b2_dynamicBody;
	playerBD.position.Set(3.5f, -0.5f);	 

	PhysicsSubsystem* temp = static_cast<PhysicsSubsystem*>(mySystem);

	player = temp->GetWorld()->CreateBody(&playerBD);

	myObject->SetPlayerBody(player);

	SetFixture();
}

void PhysicsComponent::SetFixture()
{
	fixtureDef.shape = &playerBox;
	fixtureDef.density = 0.3f;
	fixtureDef.friction = 0.3f;

	player->CreateFixture(&fixtureDef);

	ChangeCoordinatesToGraphics();
}

void PhysicsComponent::ChangeCoordinatesToGraphics()
{
	sf::Vector2f playerGraphicsPosition;
	b2Vec2 playerPhysicsPosition = player->GetPosition();

	playerGraphicsPosition.x = (playerPhysicsPosition.x - playerHalfWidth) * scalingFactor;
	playerGraphicsPosition.y = (playerPhysicsPosition.y + playerHalfWidth) * scalingFactor * -1.0f;

	myObject->UpdatePosition(playerGraphicsPosition);

}



void PhysicsComponent::Update()
{
	if (player != nullptr)
	{
		b2Vec2 dir = myObject->GetDir();
		dir.Normalize();

		dir *= speed;

		player->SetLinearVelocity(dir);		

		b2Vec2 temp = player->GetPosition();
		//std::cout << "Position -- x: " << temp.x << "   y: " << temp.y << std::endl;
		ChangeCoordinatesToGraphics();


	}
	else
	{
		std::cout << "There is no player" << std::endl;
	}

	myObject->ResetDir();
}
