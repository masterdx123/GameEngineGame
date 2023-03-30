#include <iostream>
#include <SFML/Graphics.hpp>
#include <enet/enet.h>
#include "Vector2.h"

using namespace std;

//new positions from the server
struct PhysicsData {
	int packetType = 1;
	Vector2 positions[2];
};

//client id
struct ClientData {
	int packetType = 0;
	int clientIndex;
};

//positions from 2 player objs in client
struct ClientPacket {
	int clientIndex;
	Vector2 position;
};

ENetAddress address;
ENetHost* server;
ENetEvent enetEvent;
ENetPacket* dataPacket;
PhysicsData* physicsData;
ClientPacket* clientPacket;
ClientData* clientData;

//check if Enet was initialized
void InitializeEnet()
{
	if (enet_initialize() != 0)
	{
		cout << "Enet failed to initialise!" << "\n\n";
	}
}

//Set host values to local and port to 1234
void SetAdress() 
{	
	address.host = ENET_HOST_ANY;
	address.port = 1234;
}

//create server with number of client, supported and channels and caps for upstreamand downstream bandwidth
void SetServer()
{	
	server = enet_host_create(&address, 32, 2, 0, 0);

	if (server == NULL)
	{
		cout << "Server failed to initialise!" << "\n\n";
	}
}

//Set new positions
void SetPhysicsData() {

	physicsData = new PhysicsData;

	physicsData->positions[0].x = 1.5f;
	physicsData->positions[0].y = -2.0f;
	physicsData->positions[1].x = 2.5f;
	physicsData->positions[1].y = -2.0f;
}

//initialize client 
void SetClient() 
{
	 clientPacket = new ClientPacket;

	clientPacket->clientIndex = 0;
	clientPacket->position.x = 0.0f;
	clientPacket->position.y = 0.0f;

	clientData = new ClientData;
}


void Update() {

	int clientCount = 0;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Server Window");
	sf::Event e;

	while (window.isOpen())
	{
		window.pollEvent(e);

		if (e.type == sf::Event::Closed) {
			window.close();

		}

		//Continue to check for events
		while (enet_host_service(server, &enetEvent, 0) > 0)
		{
			switch (enetEvent.type)
			{
				//first client connection	
			case ENET_EVENT_TYPE_CONNECT:

				cout << "A client connected from address " << enetEvent.peer->address.host << ":" << enetEvent.peer->address.port << ":" << clientData->clientIndex << "\n";

				clientData->clientIndex = clientCount;

				dataPacket = enet_packet_create(clientData, sizeof(ClientData), ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(enetEvent.peer, 0, dataPacket);

				enetEvent.peer->data = "This is a client";
				clientCount++;

				break;
				//client disconnects
			case ENET_EVENT_TYPE_DISCONNECT:
				cout << "The client from address " << enetEvent.peer->address.host << ":" << enetEvent.peer->address.port << " disconnected \n";

				enetEvent.peer->data = NULL;

				break;
				//receive client message
			case ENET_EVENT_TYPE_RECEIVE:

				memcpy(clientPacket, enetEvent.packet->data, enetEvent.packet->dataLength);
				physicsData->positions[clientPacket->clientIndex] = clientPacket->position;
			}
		}

		//send data to host
		dataPacket = enet_packet_create(physicsData, sizeof(PhysicsData), ENET_PACKET_FLAG_RELIABLE);
		enet_host_broadcast(server, 0, dataPacket);

		window.clear(sf::Color::Blue);
		window.display();
	}
}

//destroy pointers and stop enet
void Destroy() {
	delete physicsData;
	delete clientData;
	delete clientPacket;

	enet_host_destroy(server);
	atexit(enet_deinitialize);
}

void main()
{

	InitializeEnet();
	SetAdress();
	SetServer();
	SetPhysicsData();
	SetClient();	

	Update();

	Destroy();
}


