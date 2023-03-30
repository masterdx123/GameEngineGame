#include "GameObject.h"
#include "Component.h"

int GameObject::objectCount = 0;


GameObject::GameObject()
{
	name = new std::string();
	objectID = objectCount;
	objectCount++;
}

GameObject::GameObject(std::string name_)
{
	name = new std::string();
	objectID = objectCount;
	*name = name_;
	objectCount++;
}

GameObject::GameObject(std::string name_, std::unordered_map<ComponentType, Component*> components_)
{
	objectID = objectCount;
	*name = name_;
	components = components_;
	objectCount++;

}

void GameObject::Update(float deltaTime)
{
	//go trough all childs updates
	for (auto child : children) {

		if (child->isActive)
		{
			child->Update(deltaTime);
		}
	}
}

void GameObject::Render()
{
	//go trough all childs render
	for (auto child : children) {

		if (child->isActive)
		{
			child->Render();
		}
	}
}


void GameObject::AddComponent(Component* component_)
{	
	//add a component to the gameobject
	components.insert({ component_->GetType(), component_ });
}

Component* GameObject::GetComponent(ComponentType type_)
{
	//get the gameobject component
	auto it = components.find(type_);
	if (it == components.end())
	{
		return nullptr;
	}
	return it->second;
}





void GameObject::SetBodyPos(b2Vec2* pos_)
{
	//set a body pos
	pos.push_back(pos_);
}

GameObject* GameObject::AddChild(GameObject* child_)
{
	//add a child to a gameobject
	child_->SetParent(this);
	children.push_back(child_);
	return child_;
}

GameObject* GameObject::GetChild(int index_) const
{
	//return child of gameobject
	return children[index_];
}

GameObject* GameObject::Find(const std::string& name_) const
{
	//find child of a gameobject 
	if (*this->name == name_)
	{
		return const_cast<GameObject*>(this);
	}
	for (auto child : children)
	{
		auto result = child->Find(name_);
		if (result != nullptr)
		{
			return result;
		}
	}
	return nullptr;
}

GameObject* GameObject::GetParent() const
{
	//get parent of a gameobject
	return parent;
}

void GameObject::SetParent(GameObject* parent_)
{
	//set gameobject to be a parent
	this->parent = parent_;
	parent->children.push_back(this);
}

void GameObject::RemoveChild(GameObject* child_)
{
	//remove a child from a gameobject
	auto it = std::find(children.begin(), children.end(), child_);
	if (it != children.end())
	{
		children.erase(it);
	}
}

int GameObject::GetChildCount() const
{
	//get the child count from a gameobject
	return static_cast<int>(children.size());
}


