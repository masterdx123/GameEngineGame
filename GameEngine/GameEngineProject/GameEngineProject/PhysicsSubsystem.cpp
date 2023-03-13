#include "PhysicsSubsystem.h"
#include "Component.h"
#include "BoxColl2D.h"
#include "CircleColl2D.h"

Component* PhysicsSubsystem::AddComponent(Component* component_)
{
	if (component_->GetType() == ComponentType::BoxColl2D)
	{
		BoxColl2D* temp = static_cast<BoxColl2D*>(component_);
		components->push_back(temp);
		return (components->back());
	}
	else if (component_->GetType() == ComponentType::CircleColl2D)
	{
		CircleColl2D* temp = static_cast<CircleColl2D*>(component_);
		components->push_back(temp);
		return (components->back());
	}
	else
	{
		std::cout << "Tried to push a non-physics component to the physics subsystem" << std::endl;
		return nullptr;
	}
}

void PhysicsSubsystem::Update()
{
	// update components bellonging to physics subsystem
	for (int i = 0; i < components->size(); i++)
	{
		components->at(i)->Update();
	}
}
