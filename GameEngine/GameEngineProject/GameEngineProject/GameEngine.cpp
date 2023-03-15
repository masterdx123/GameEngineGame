#include "GameEngine.h"
#include "GameObject.h"
#include "PhysicsSubsystem.h"
#include "GraphicsSubsystem.h"
#include "IOSubsystem.h"
#include "EventQueue.h"


GameEngine::GameEngine()
{
	gameObjects = new std::vector<GameObject*>;
	subsystems = new std::vector<Subsystem*>;
	eventQueue = new EventQueue();

	PhysicsSubsystem* physicsSubsystem = new PhysicsSubsystem(eventQueue, gameObjects);
	GraphicsSubsystem* graphicsSubsystem = new GraphicsSubsystem(eventQueue, gameObjects);
	IOSubsystem* ioSubsystem = new IOSubsystem(eventQueue, gameObjects);

	subsystems->push_back(graphicsSubsystem);
	subsystems->push_back(physicsSubsystem);	
	subsystems->push_back(ioSubsystem);

	SetupGame();
}

GameEngine::~GameEngine()
{
	for (int i = 0; i < subsystems->size(); i++)
	{
		delete subsystems->at(i);
	}

	for (int i = 0; i < gameObjects->size(); i++)
	{
		delete gameObjects->at(i);
	}

	subsystems->clear();
	gameObjects->clear();

	delete subsystems;
	delete gameObjects;
	delete eventQueue;
}

int GameEngine::Update()
{
	int i;

	for (i = 0; i < subsystems->size(); i++)
	{
		subsystems->at(i)->Update();
	}

	int eventQueueSize = eventQueue->events.size();

	if (eventQueueSize > 0)
	{
		for (i = 0; i < eventQueueSize; i++)
		{	

			if (eventQueue->events[i]->systems.size() == 0)
			{
				delete eventQueue->events[i];
				eventQueue->events.erase(eventQueue->events.begin() + i);
			}
		}
	}

	GraphicsSubsystem* tempptr = static_cast<GraphicsSubsystem*>(subsystems->at(0));

	if (tempptr->GetWindow()->isOpen())
	{
		

		return true;
	}

	return false;
}

void GameEngine::SetupGame()
{
	// Player Setup
	gameObjects->push_back(new GameObject("Player"));
	/*
	
	*/
	

	GraphicsSubsystem* tempptr = static_cast<GraphicsSubsystem*>(subsystems->at(0));	

	BoxShape2D playerBoxShape(gameObjects->back(), subsystems->at(0), tempptr->GetWindow(), Vector2(2.5f, -2.0f), Vector2(50.0f, 50.0f), "../Textures/catGame.jpg");
	PhysicsComponent playerPhysics(gameObjects->back(), subsystems->at(1), 0.5f);	
	IOComponent playerIO(gameObjects->back(), subsystems->at(2));
	
	gameObjects->back()->AddComponent(subsystems->at(0)->AddComponent(&playerBoxShape));
	gameObjects->back()->AddComponent(subsystems->at(1)->AddComponent(&playerPhysics));	
	gameObjects->back()->AddComponent(subsystems->at(2)->AddComponent(&playerIO));
	
	

	gameObjects->push_back(new GameObject("Enemy"));

	BoxShape2D enemyBoxShape(gameObjects->back(), subsystems->at(0), tempptr->GetWindow(), Vector2(2.5f, -0.5f), Vector2(100.0f, 100.0f), "../Textures/keyboardcat.jpg");
	PhysicsComponent enemyPhysics(gameObjects->back(), subsystems->at(1),0.25f);

	gameObjects->back()->AddComponent(subsystems->at(0)->AddComponent(&enemyBoxShape));
	gameObjects->back()->AddComponent(subsystems->at(1)->AddComponent(&enemyPhysics));
}
