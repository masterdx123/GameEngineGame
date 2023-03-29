#pragma once

//#include "Component.h"
//#include "Transform.h"
#include "Common.h"
#include "SFML/Graphics.hpp"
#include <Box2D/Box2D.h>

class Component;

class GameObject {
public:
	static int objectCount;

	GameObject();
	GameObject(std::string name_);
	GameObject(std::string name_, std::unordered_map<ComponentType, Component*> components_);
	~GameObject() {};

	//Transform transform;
	bool isActive;

	virtual void Update(float deltaTime);
	virtual void Render();
	
	void AddComponent(Component* component_);
	Component* GetComponent(ComponentType type_);
	std::string GetName() { return *name; };
	int GetObjectID() { return objectID; };
	void SetName(std::string name_) { *name = name_; }

	void SetBody(b2Body* playerBody_) { playerBody = playerBody_; }
	b2Body* GetBody() { return playerBody; };

	void SetBodyPos(b2Vec2* pos_);
	std::vector<b2Vec2*> GetBodyPos() { return pos; };

	
	GameObject* AddChild(GameObject* child_);
	GameObject* GetChild(int index_) const;
	GameObject* Find(const std::string& name_) const;
	GameObject* GetParent() const;
	void SetParent(GameObject* parent_);
	void RemoveChild(GameObject* child_);
	int GetChildCount() const; 	

	inline void UpdatePosition(sf::Vector2f position_) { position = position_; }
	inline sf::Vector2f GetPosition() { return position; }
	inline b2Vec2 GetDir() { return direction; }
	inline void SetDir(b2Vec2 direction_) { direction = direction_; }
	inline void ResetDir() { direction.x = 0.0f; direction.y = 0.0f; }

	inline void SetClientIndex(int clientIndex_) { clientIndex = clientIndex_; }
	inline int GetClientIndex() { return clientIndex; }

private:
	int objectID;
	std::string* name;
	GameObject* parent;
	std::vector<GameObject*> children;
	std::unordered_map<ComponentType, Component*> components;
	b2Body* playerBody;
	sf::Vector2f position;
	b2Vec2 direction;
	std::vector<b2Vec2*> pos;
	int clientIndex;
};
