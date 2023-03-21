#include "GameEngine.h"
#include "GameObject.h"
#include "PhysicsSubsystem.h"
#include "GraphicsSubsystem.h"
#include "IOSubsystem.h"
#include "AISubsystem.h"
#include "EventQueue.h"


GameEngine::GameEngine()
{
	gameObjects = new std::vector<GameObject*>;
	subsystems = new std::vector<Subsystem*>;
	eventQueue = new EventQueue();

	// Create the game subsystems
	PhysicsSubsystem* physicsSubsystem = new PhysicsSubsystem(eventQueue, gameObjects);
	GraphicsSubsystem* graphicsSubsystem = new GraphicsSubsystem(eventQueue, gameObjects);
	IOSubsystem* ioSubsystem = new IOSubsystem(eventQueue, gameObjects);
	AISubsystem* aiSubsystem = new AISubsystem(eventQueue, gameObjects);

	// Push all systems into the Vector of subsystems
	subsystems->push_back(graphicsSubsystem);
	subsystems->push_back(physicsSubsystem);
	subsystems->push_back(ioSubsystem);
	subsystems->push_back(aiSubsystem);

	SetupGame();
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

		return true;
	}

	return false;
}

void GameEngine::SetupGame()
{
	// Player Setup
	gameObjects->push_back(new GameObject("Player"));	

	GraphicsSubsystem* tempptr = static_cast<GraphicsSubsystem*>(subsystems->at(0));	

	BoxShape2D playerBoxShape(gameObjects->back(), subsystems->at(0), tempptr->GetWindow(), Vector2(2.5f, -2.0f), Vector2(50.0f, 50.0f), "../Textures/catGame.jpg");
	PhysicsComponent playerPhysics(gameObjects->back(), subsystems->at(1), 0.125f);	
	IOComponent playerIO(gameObjects->back(), subsystems->at(2));
	
	gameObjects->back()->AddComponent(subsystems->at(0)->AddComponent(&playerBoxShape));
	gameObjects->back()->AddComponent(subsystems->at(1)->AddComponent(&playerPhysics));	
	gameObjects->back()->AddComponent(subsystems->at(2)->AddComponent(&playerIO));
	
	
	
	// Enemy Setup
	gameObjects->push_back(new GameObject("Enemy"));

	BoxShape2D enemyBoxShape(gameObjects->back(), subsystems->at(0), tempptr->GetWindow(), Vector2(2.5f, -1.0f), Vector2(100.0f, 100.0f), "../Textures/keyboardcat.jpg");
	PhysicsComponent enemyPhysics(gameObjects->back(), subsystems->at(1),0.25f);
	AIComponent enemyAI(gameObjects->back(), subsystems->at(3));

	enemyAI.AddBehaviour(BehaviourType::Patrol, "Patrolling!");
	enemyAI.AddBehaviour(BehaviourType::Hunt, "Hunting!");

	gameObjects->back()->AddComponent(subsystems->at(0)->AddComponent(&enemyBoxShape));
	gameObjects->back()->AddComponent(subsystems->at(1)->AddComponent(&enemyPhysics));
	gameObjects->back()->AddComponent(subsystems->at(3)->AddComponent(&enemyAI));
}
