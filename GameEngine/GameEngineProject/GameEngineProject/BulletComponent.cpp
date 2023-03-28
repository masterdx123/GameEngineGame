//#include "BulletComponent.h"
//#include "EventQueue.h"
//#include "SFML/Graphics.hpp"
//#include "AISubsystem.h"
//#include "GameObject.h"
//
//BulletComponent& BulletComponent::operator=(const BulletComponent& other)
//{
//	if (this == &other)
//	{
//		return *this;
//	}
//
//	memcpy(this, &other, sizeof(other));
//	return *this;
//}
//
//void BulletComponent::Update()
//{
//
//	if (isShot)
//	{
//		b2Vec2 dir;
//		float speed = 0.2;
//
//		dir.x = sf::Mouse::getPosition().x - myObject->GetBody()->GetPosition().x;
//		dir.y = sf::Mouse::getPosition().y - myObject->GetBody()->GetPosition().y;
//
//		myObject->GetBody()->SetLinearVelocity(speed * dir);
//
//		
//	}
//}
