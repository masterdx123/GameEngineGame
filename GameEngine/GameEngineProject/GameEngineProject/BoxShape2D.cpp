#include "BoxShape2D.h"
#include "GameObject.h"

class GameObject;

BoxShape2D& BoxShape2D::operator=(const BoxShape2D& other)
{
	if (this == &other)
	{
		return *this;
	}

	memcpy(this, &other, sizeof(other));
	return *this;
}

// Update the shape of the object every frame and draw it
void BoxShape2D::Update()
{	
	
	//get font

	if (!font.loadFromFile("../Fonts/Raleway-Black.ttf")) {
		std::cout << "Font was not found!" << "\n";
	}

	//setup text
	text.setFont(font);
	text.setCharacterSize(24);
	text.setPosition(50, 50);
	text.setFillColor(sf::Color::White);
	text.setString("Enemies found: 1");
	
	

	myShape->setPosition(myObject->GetPosition());	
	window->draw(*myShape);
	window->draw(text);
}
