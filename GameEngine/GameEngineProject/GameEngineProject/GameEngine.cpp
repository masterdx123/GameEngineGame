#include "GameEngine.h"
#include "GameObject.h"
#include "PhysicsSubsystem.h"
#include "GraphicsSubsystem.h"
#include "IOSubsystem.h"
#include "AISubsystem.h"
#include "NetSubsystem.h"
#include "UISubsystem.h"
#include "EventQueue.h"

//NetworkComponent* temp;

GameEngine::GameEngine()
{

	gameObjects = new std::vector<GameObject*>;
	subsystems = new std::vector<Subsystem*>;
	eventQueue = new EventQueue();

	// Create the game subsystems
	PhysicsSubsystem* physicsSubsystem = new PhysicsSubsystem(eventQueue, gameObjects);
	subsystems->push_back(physicsSubsystem);
	GraphicsSubsystem* graphicsSubsystem = new GraphicsSubsystem(eventQueue, gameObjects);
	subsystems->push_back(graphicsSubsystem);
	IOSubsystem* ioSubsystem = new IOSubsystem(eventQueue, gameObjects);
	subsystems->push_back(ioSubsystem);
	AISubsystem* aiSubsystem = new AISubsystem(eventQueue, gameObjects);
	subsystems->push_back(aiSubsystem);
	NetSubsystem* netSubsystem = new NetSubsystem(eventQueue, gameObjects);
	subsystems->push_back(netSubsystem);
	UISubsystem* uiSubsystem = new UISubsystem("../jsonFiles/jsonFile.json", this);

	// Push all systems into the Vector of subsystems
	
	
	
	
	


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

void GameEngine::SetupGame()
{
	//// Player Setup
	//gameObjects->push_back(new GameObject("Player"));	

	//GraphicsSubsystem* tempptr = static_cast<GraphicsSubsystem*>(subsystems->at(0));	

	//BoxShape2D* playerBoxShape = new BoxShape2D(gameObjects->back(), subsystems->at(0), tempptr->GetWindow(), Vector2(2.5f, -2.0f), Vector2(50.0f, 50.0f), "../Textures/catGame.jpg");
	//PhysicsComponent* playerPhysics = new PhysicsComponent(gameObjects->back(), subsystems->at(1), 0.125f);	
	//IOComponent* playerIO = new IOComponent(gameObjects->back(), subsystems->at(2));
	//NetComponent* player1Network = new NetComponent(gameObjects->back(), subsystems->at(4));
	//
	//gameObjects->back()->AddComponent(subsystems->at(0)->AddComponent(playerBoxShape));
	//gameObjects->back()->AddComponent(subsystems->at(1)->AddComponent(playerPhysics));	
	//gameObjects->back()->AddComponent(subsystems->at(2)->AddComponent(playerIO));
	//gameObjects->back()->AddComponent(subsystems->at(4)->AddComponent(player1Network));

	//
	////Bullet setup 
	//gameObjects->push_back(new GameObject("Bullet"));

	//std::vector<Vector2> bulletvec = { Vector2(0, 0) };

	//BoxShape2D* bulletBoxShape = new BoxShape2D(gameObjects->back(), subsystems->at(0), tempptr->GetWindow(), Vector2(2.5f, -1.8f), Vector2(25.0f, 25.0f), "../Textures/catGame.jpg");
	//PhysicsComponent* bulletPhysics = new PhysicsComponent(gameObjects->back(), subsystems->at(1), 0.0625f);
	//AIComponent* bulletAI = new AIComponent(gameObjects->back(), subsystems->at(3),bulletvec );
	//
	////BulletComponent bulletComp(gameObjects->back(), subsystems->at(3));

	//gameObjects->back()->AddComponent(subsystems->at(0)->AddComponent(bulletBoxShape));
	//gameObjects->back()->AddComponent(subsystems->at(1)->AddComponent(bulletPhysics));
	////gameObjects->back()->AddComponent(subsystems->at(2)->AddComponent(&bulletIO));
	//gameObjects->back()->AddComponent(subsystems->at(3)->AddComponent(bulletAI));

	////gameObjects->back()->AddComponent(subsystems->at(3)->AddComponent(&bulletComp));
	//
	//
	//

	//// Player2 Setup
	//gameObjects->push_back(new GameObject("Player2"));

	//BoxShape2D* player2BoxShape = new BoxShape2D(gameObjects->back(), subsystems->at(0), tempptr->GetWindow(), Vector2(1.5f, -2.0f), Vector2(50.0f, 50.0f), "../Textures/enemycat.jpg");
	//PhysicsComponent* player2Physics = new PhysicsComponent(gameObjects->back(), subsystems->at(1), 0.125f);
	//IOComponent* player2IO = new IOComponent(gameObjects->back(), subsystems->at(2));
	//NetComponent* player2Network = new NetComponent(gameObjects->back(), subsystems->at(4));

	//gameObjects->back()->AddComponent(subsystems->at(0)->AddComponent(player2BoxShape));
	//gameObjects->back()->AddComponent(subsystems->at(1)->AddComponent(player2Physics));
	//gameObjects->back()->AddComponent(subsystems->at(2)->AddComponent(player2IO));
	//gameObjects->back()->AddComponent(subsystems->at(4)->AddComponent(player2Network));
	
	
	
	//// Enemy Setup
	//gameObjects->push_back(new GameObject("Enemy"));

	//std::vector<Vector2> enemyWaypoints = { Vector2(1.0f, -1.0f), Vector2(3.0f,-1.0f) };

	//BoxShape2D* enemyBoxShape = new BoxShape2D(gameObjects->back(), subsystems->at(0), tempptr->GetWindow(), Vector2(2.5f, -1.0f), Vector2(100.0f, 100.0f), "../Textures/keyboardcat.jpg");
	//PhysicsComponent* enemyPhysics = new PhysicsComponent(gameObjects->back(), subsystems->at(1),0.25f);
	//AIComponent* enemyAI = new AIComponent(gameObjects->back(), subsystems->at(3) ,enemyWaypoints);

	//enemyAI->AddBehaviour(BehaviourType::Patrol, "Patrolling!");
	//enemyAI->AddBehaviour(BehaviourType::Hunt, "Hunting!");

	//gameObjects->back()->AddComponent(subsystems->at(0)->AddComponent(enemyBoxShape));
	//gameObjects->back()->AddComponent(subsystems->at(1)->AddComponent(enemyPhysics));
	//gameObjects->back()->AddComponent(subsystems->at(3)->AddComponent(enemyAI));
}
