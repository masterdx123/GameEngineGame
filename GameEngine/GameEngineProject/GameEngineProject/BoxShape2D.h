#pragma once

#include "Component.h"
#include "SFML/Graphics.hpp"
#include "Vector2.h"

class GameObject;


class BoxShape2D : public Component {
public:
	BoxShape2D(GameObject* myObject_, Subsystem* mySystem_, sf::RenderWindow* window_, Vector2 pos_, Vector2 size_, sf::Texture objTexture_) : Component(ComponentType::BoxShape2D, myObject_, mySystem_) {
		myShape = new sf::RectangleShape;
		window = window_;		
		sf::Vector2f temp(pos_.x, pos_.y);		
		myShape->setSize(sf::Vector2f(size_.x, size_.y));
		myShape->setPosition(temp);

		//merda de linha n funciona a texturaporque mete a null
		myShape->setTexture(&objTexture_);

		//cant get obj to receive shape because GameObject is undefined
		myObject = myObject_;
		myObject[0].SetPlayerShape(myShape);
	};
	BoxShape2D(const BoxShape2D& other) : Component(ComponentType::BoxShape2D, other.myObject, other.mySystem) {
		myShape = new sf::RectangleShape;
		window = other.window;
		myShape->setSize(other.myShape->getSize());
		myShape->setPosition(other.myShape->getPosition());

		//merda de linha n funciona a texturaporque mete a null
		myShape->setTexture(other.myShape->getTexture());

		//cant get obj to receive shape because GameObject is undefined
		myObject = other.myObject;
		myObject->SetPlayerShape(myShape);
	};

	~BoxShape2D() { delete myShape; };
	BoxShape2D& operator=(const BoxShape2D& other);

	void Update();

protected:
	sf::RectangleShape* myShape;
	sf::RenderWindow* window;	
	GameObject* myObject;
};