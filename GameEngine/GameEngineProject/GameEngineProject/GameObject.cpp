#include "GameObject.h"

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
	for (auto child : children) {

		if (child->isActive)
		{
			child->Update(deltaTime);
		}
	}
}

void GameObject::Render()
{
	for (auto child : children) {

		if (child->isActive)
		{
			child->Render();
		}
	}
}

void GameObject::AddComponent(Component* component_)
{	
	components.insert({ component_->GetType(), component_ });
};

Component* GameObject::GetComponent(ComponentType type_)
{
	auto it = components.find(type_);
	return it->second;
}

GameObject* GameObject::AddChild(GameObject* child_)
{
	child_->SetParent(this);
	children.push_back(child_);
	return child_;
}

GameObject* GameObject::GetChild(int index_) const
{
	return children[index_];
}

GameObject* GameObject::Find(const std::string& name_) const
{
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
	return parent;
}

void GameObject::SetParent(GameObject* parent_)
{
	this->parent = parent_;
	transform.SetParent(&parent->transform);
	parent->children.push_back(this);
}

void GameObject::RemoveChild(GameObject* child_)
{
	auto it = std::find(children.begin(), children.end(), child_);
	if (it != children.end())
	{
		child_->transform.SetParent(nullptr);
		children.erase(it);
	}
}

int GameObject::GetChildCount() const
{
	return static_cast<int>(children.size());
}


