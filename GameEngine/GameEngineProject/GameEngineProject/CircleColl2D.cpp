#include "CircleColl2D.h"

CircleColl2D& CircleColl2D::operator=(const CircleColl2D& other)
{
	if (this == &other)
	{
		return *this;
	}

	memcpy(this, &other, sizeof(other));
	return *this;
}
