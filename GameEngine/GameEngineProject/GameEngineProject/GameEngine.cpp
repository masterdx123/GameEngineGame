#include "GameEngine.h"
#include "GameObject.h"
#include "PhysicsSubsystem.h"
#include "GraphicsSubsystem.h"
#include "IOSubsystem.h"
#include "AISubsystem.h"
#include "NetworkSubsystem.h"
#include "EventQueue.h"

NetworkComponent* temp;

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
	NetworkSubsystem* netSubsystem = new NetworkSubsystem(eventQueue, gameObjects);

	// Push all systems into the Vector of subsystems
	subsystems->push_back(graphicsSubsystem);
	subsystems->push_back(physicsSubsystem);
	subsystems->push_back(ioSubsystem);
	subsystems->push_back(aiSubsystem);
	subsystems->push_back(netSubsystem);

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
		sf::Event e;

		tempptr->GetWindow()->pollEvent(e);

		if (e.type == sf::Event::Closed) {

			if (temp->GetPeer() != NULL)
			{
				enet_peer_disconnect_now(temp->GetPeer(), 0);
			}

			tempptr->GetWindow()->close();

		}
		if (e.type == sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			tempptr->GetWindow()->close();
		}

		while (enet_host_service(temp->GetClient(), temp->GetEnetEvent(), 0) > 0)
		{
			switch (temp->GetEnetEvent()->type) {

				

			case ENET_EVENT_TYPE_RECEIVE:

				memcpy(temp->GetPacketType(), temp->GetEnetEvent()->packet->data, sizeof(int));

				if (*temp->GetPacketType() == 0)
				{
					std::cout << "Packet Received!\n";
					memcpy(temp->GetClientData(), temp->GetEnetEvent()->packet->data, sizeof(ClientData));
					*temp->GetClientIndex() = temp->GetClientData()->clientIndex;
				}
				else if (*temp->GetPacketType() == 1)
				{
					memcpy(temp->GetServerData(), temp->GetEnetEvent()->packet->data, sizeof(PhysicsData));
					for (int i = 0; i < 2; i++)
					{
						if (i != *temp->GetClientIndex())
						{
							b2Vec2 enemyPos = b2Vec2(temp->GetServerData()->positions[i].x, temp->GetServerData()->positions[i].y);
							gameObjects->at(1)->GetBody()->SetTransform(enemyPos, 0.0f);
						}
					}
				}

				break;
				//cout << "Packet received!\n";
				//memcpy(newPosition, enetEvent.packet->data, enetEvent.packet->dataLength);
				//cout << newPosition->x << "," << newPosition->y << "\n";
				//enemy.setPosition(sf::Vector2f(newPosition->x, newPosition->y));
				//break;
			}
		}

		temp->GetClientPacket()->clientIndex = *temp->GetClientIndex();
		temp->GetClientPacket()->position.x = gameObjects->at(0)->GetBody()->GetPosition().x;
		temp->GetClientPacket()->position.y = gameObjects->at(0)->GetBody()->GetPosition().y;

		*temp->GetDataPacket() = *enet_packet_create(temp->GetClientPacket(), sizeof(ClientPacket), ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(temp->GetPeer(), 0, temp->GetDataPacket());

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


	// Player2 Setup
	gameObjects->push_back(new GameObject("Player2"));

	GraphicsSubsystem* tempptr2 = static_cast<GraphicsSubsystem*>(subsystems->at(0));

	BoxShape2D player2BoxShape(gameObjects->back(), subsystems->at(0), tempptr2->GetWindow(), Vector2(1.5f, -2.0f), Vector2(50.0f, 50.0f), "../Textures/catGame.jpg");
	PhysicsComponent player2Physics(gameObjects->back(), subsystems->at(1), 0.125f);
	IOComponent player2IO(gameObjects->back(), subsystems->at(2));

	gameObjects->back()->AddComponent(subsystems->at(0)->AddComponent(&player2BoxShape));
	gameObjects->back()->AddComponent(subsystems->at(1)->AddComponent(&player2Physics));
	gameObjects->back()->AddComponent(subsystems->at(2)->AddComponent(&player2IO));
	
	
	
	// Enemy Setup
	gameObjects->push_back(new GameObject("Enemy"));

	std::vector<Vector2> enemyWaypoints = { Vector2(1.0f, -1.0f), Vector2(3.0f,-1.0f) };

	BoxShape2D enemyBoxShape(gameObjects->back(), subsystems->at(0), tempptr->GetWindow(), Vector2(2.5f, -1.0f), Vector2(100.0f, 100.0f), "../Textures/keyboardcat.jpg");
	PhysicsComponent enemyPhysics(gameObjects->back(), subsystems->at(1),0.25f);
	AIComponent enemyAI(gameObjects->back(), subsystems->at(3) ,enemyWaypoints);

	enemyAI.AddBehaviour(BehaviourType::Patrol, "Patrolling!");
	enemyAI.AddBehaviour(BehaviourType::Hunt, "Hunting!");

	gameObjects->back()->AddComponent(subsystems->at(0)->AddComponent(&enemyBoxShape));
	gameObjects->back()->AddComponent(subsystems->at(1)->AddComponent(&enemyPhysics));
	gameObjects->back()->AddComponent(subsystems->at(3)->AddComponent(&enemyAI));
}
