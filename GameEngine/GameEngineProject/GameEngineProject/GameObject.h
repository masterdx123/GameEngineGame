#pragma once

#include "Component.h"
#include "Transform.h"
#include "Common.h"
#include "SFML/Graphics.hpp"

class GameObject {
public:
	static int objectCount;

	GameObject();
	GameObject(std::string name_);
	GameObject(std::string name_, std::unordered_map<ComponentType, Component*> components_);
	~GameObject() {};

	Transform transform;
	bool isActive;

	virtual void Update(float deltaTime);
	virtual void Render();
	
	void AddComponent(Component* component_);
	Component* GetComponent(ComponentType type_);
	std::string GetName() { return *name; };
	int GetObjectID() { return objectID; };
	void SetName(std::string name_) { *name = name_; }
	void SetPlayerShape(sf::RectangleShape* playerShape_) { playerShape = playerShape_; }
	sf::RectangleShape* GetPlayerShape() { return playerShape; }

	GameObject* AddChild(GameObject* child_);
	GameObject* GetChild(int index_) const;
	GameObject* Find(const std::string& name_) const;
	GameObject* GetParent() const;
	void SetParent(GameObject* parent_);
	void RemoveChild(GameObject* child_);
	int GetChildCount() const; 	

private:
	int objectID;
	std::string* name;
	GameObject* parent;
	std::vector<GameObject*> children;
	std::unordered_map<ComponentType, Component*> components;
	sf::RectangleShape* playerShape;
};
