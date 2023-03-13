#pragma once

#include "Common.h"


class GameObject;
class Subsystem;
class EventQueue;



class GameEngine {
public:
	GameEngine();
	~GameEngine();

	int Update();
	void SetupGame();

private:
	std::vector<GameObject*>* gameObjects;
	std::vector<Subsystem*>* subsystems;
	EventQueue* eventQueue;
};
