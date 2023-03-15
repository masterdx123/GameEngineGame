#pragma once

#include "Component.h"
#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include "Vector2.h"



class BoxShape2D : public Component {
public:
	BoxShape2D(GameObject* myObject_, Subsystem* mySystem_, sf::RenderWindow* window_, Vector2 pos_, Vector2 size_, std::string fileName_) : Component(ComponentType::BoxShape2D, myObject_, mySystem_) {
		myShape = new sf::RectangleShape;
		window = window_;		
		sf::Vector2f temp(pos_.x, pos_.y);		
		myShape->setSize(sf::Vector2f(size_.x, size_.y));
		//myShape->setPosition(temp);

		objTexture = new sf::Texture;

		if (!objTexture->loadFromFile(fileName_))
		{
			std::cout << "Texture did not load!" << "\n";
		}

		myShape->setTexture(objTexture);

		b2Position = new b2Vec2;
		b2Position->Set(temp.x, temp.y);
		myObject->SetBodyPos(b2Position);
		
	};
	BoxShape2D(const BoxShape2D& other) : Component(ComponentType::BoxShape2D, other.myObject, other.mySystem) {
		myShape = new sf::RectangleShape;
		objTexture = new sf::Texture;
		b2Position = new b2Vec2;
		window = other.window;
		myShape->setSize(other.myShape->getSize());
		myShape->setPosition(other.myShape->getPosition());
		myShape->setTexture(other.myShape->getTexture());
	};

	~BoxShape2D() { delete myShape; };
	BoxShape2D& operator=(const BoxShape2D& other);

	void Update();

protected:
	sf::RectangleShape* myShape;
	sf::RenderWindow* window;	
	sf::Texture* objTexture;
	b2Vec2* b2Position;

};