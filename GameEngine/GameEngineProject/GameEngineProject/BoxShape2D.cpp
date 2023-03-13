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
	window->draw(*myShape);		
}
