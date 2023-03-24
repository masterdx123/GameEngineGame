#include "NetworkComponent.h"

NetworkComponent& NetworkComponent::operator=(const NetworkComponent& other)
{
	if (this == &other)
	{
		return *this;
	}

	memcpy(this, &other, sizeof(other));
	return *this;
}

void NetworkComponent::Update()
{
}
