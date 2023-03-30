#include "GameEngine.h"
#include "GameObject.h"
#include "PhysicsSubsystem.h"
#include "GraphicsSubsystem.h"
#include "IOSubsystem.h"
#include "GameplaySubsystem.h"
#include "NetSubsystem.h"
#include "UISubsystem.h"
#include "AudioSubsystem.h"
#include "EventQueue.h"

//NetworkComponent* temp;

GameEngine::GameEngine()
{

	gameObjects = new std::vector<GameObject*>;
	subsystems = new std::vector<Subsystem*>;
	eventQueue = new EventQueue();

	// Create the game subsystems
	GraphicsSubsystem* graphicsSubsystem = new GraphicsSubsystem(eventQueue, gameObjects);
	subsystems->push_back(graphicsSubsystem);
	PhysicsSubsystem* physicsSubsystem = new PhysicsSubsystem(eventQueue, gameObjects);
	subsystems->push_back(physicsSubsystem);	
	UISubsystem* uiSubsystem = new UISubsystem(eventQueue, gameObjects);
	subsystems->push_back(uiSubsystem);
	GameplaySubsystem* gameplaySubsystem = new GameplaySubsystem(eventQueue, gameObjects);
	subsystems->push_back(gameplaySubsystem);
	NetSubsystem* netSubsystem = new NetSubsystem(eventQueue, gameObjects);
	subsystems->push_back(netSubsystem);

	IOSubsystem* ioSubsystem = new IOSubsystem("../jsonFiles/jsonFile.json", this);
}

GameEngine::~GameEngine()
{
	// delete all subsystems
	for (int i = 0; i < subsystems->size(); i++)
	{
		delete subsystems->at(i);
	}

	// delete all gameobjects
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

	// Update all subsystems
	for (i = 0; i < subsystems->size(); i++)
	{
		subsystems->at(i)->Update();
	}


	// Receive events from event queue

	for (auto it = eventQueue->events.begin(); it != eventQueue->events.end(); ++it)
	{
		if ((*it)->systems.size() != 0)
			eventQueue->eventsBuffer.push_back(*it);
	}

	eventQueue->events.clear();

	for (auto it = eventQueue->eventsBuffer.begin(); it != eventQueue->eventsBuffer.end(); ++it)
	{
		eventQueue->events.push_back(*it);
	}

	eventQueue->eventsBuffer.clear();
	


	// Run the game while graphics window is open
	GraphicsSubsystem* tempptr = static_cast<GraphicsSubsystem*>(subsystems->at(0));

	

	if (tempptr->GetWindow()->isOpen())
	{
		sf::Event e;

		tempptr->GetWindow()->pollEvent(e);

		if (e.type == sf::Event::Closed) {

			

			tempptr->GetWindow()->close();

		}
		if (e.type == sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			tempptr->GetWindow()->close();
		}

		

		return true;
	}

	return false;
}
