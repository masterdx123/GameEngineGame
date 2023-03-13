#pragma once

#include "Component.h"
#include "Common.h"
#include "Vector2.h" 


class Transform {
public:
	Transform() : position(0, 0), scale(1, 1), rotation(0), parent(nullptr) {};
	Transform(Vector2 position_, Vector2 scale_, float rotation_) : position(position_), scale(scale_), rotation(rotation_) , parent(nullptr) {};
	~Transform() {};

	// Parent-Child relations
	void SetParent(Transform* parent) { this->parent = parent; };
	Transform* GetParent() const { return parent; }
	void AddChild(Transform* child) { children.push_back(child); }
	const std::vector<Transform*>& GetChildren() const { return children; }

	// Translation, Rotation, Scalling
	void Translation(Vector2 translation) { position += translation; };
	void Rotate(float angle) { rotation += angle; };
	void Scale(Vector2 scale) { this->scale *= scale; };

	Vector2 position;
	Vector2 scale;
	float rotation;	

private:
	Transform* parent;
	std::vector<Transform*> children;
};
