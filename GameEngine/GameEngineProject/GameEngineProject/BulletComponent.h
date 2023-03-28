//#pragma once
//
//#include "Component.h"
//
//class BulletComponent : public Component {
//public:
//	BulletComponent(GameObject* myObject_, Subsystem* mySystem_) : Component(ComponentType::Bullet, myObject_, mySystem_) {
//		isShot = false;
//	};
//	BulletComponent(const BulletComponent& other) : Component(other) {
//		isShot = other.isShot;
//	};
//
//	BulletComponent& operator=(const BulletComponent& other);
//
//	
//	
//	void Update();
//private:
//	
//
//};