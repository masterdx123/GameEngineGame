#include "GameEngine.h"
#include "GameObject.h"
#include "PhysicsSubsystem.h"
#include "GraphicsSubsystem.h"
#include "EventQueue.h"

GameEngine::GameEngine()
{
	gameObjects = new std::vector<GameObject*>;
	subsystems = new std::vector<Subsystem*>;
	eventQueue = new EventQueue();

	PhysicsSubsystem* physicsSubsystem = new PhysicsSubsystem(eventQueue, gameObjects);
	GraphicsSubsystem* graphicsSubsystem = new GraphicsSubsystem(eventQueue, gameObjects);

	subsystems->push_back(physicsSubsystem);
	subsystems->push_back(graphicsSubsystem);	

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

	GraphicsSubsystem* tempptr = static_cast<GraphicsSubsystem*>(subsystems->at(1));

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
	sf::Texture objTexture;

	if (!objTexture.loadFromFile("../Textures/catGame.jpg"))
	{
		std::cout << "Texture did not load!" << "\n";
	}

	GraphicsSubsystem* tempptr = static_cast<GraphicsSubsystem*>(subsystems->at(1));

	//BoxColl2D boxColl(gameObjects->back(), subsystems->at(0));
	BoxShape2D playerBoxShape(gameObjects->back(), subsystems->at(1), tempptr->GetWindow(), Vector2(400.0f, 200.0f), Vector2(50.0f, 50.0f), objTexture);
	
	//gameObjects->back()->AddComponent(subsystems->at(0)->AddComponent(&boxColl));
	gameObjects->back()->AddComponent(subsystems->at(1)->AddComponent(&playerBoxShape));
	

	gameObjects->push_back(new GameObject("Enemy"));
	BoxShape2D enemyBoxShape(gameObjects->back(), subsystems->at(1), tempptr->GetWindow(), Vector2(600.0f, 300.0f), Vector2(100.0f, 100.0f), objTexture);
	gameObjects->back()->AddComponent(subsystems->at(1)->AddComponent(&enemyBoxShape));
}
