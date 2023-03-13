#include "BoxColl2D.h"

BoxColl2D& BoxColl2D::operator=(const BoxColl2D& other)
{
	if (this == &other)
	{
		return *this;
	}

	memcpy(this, &other, sizeof(other));
	return *this;
}
