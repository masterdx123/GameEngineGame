#pragma once

#include "Component.h"
#include <enet\enet.h>
#include "EventQueue.h"


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

class NetComponent : public Component {
public:
	NetComponent(GameObject* myObject_, Subsystem* mySystem_) : Component(ComponentType::Network, myObject_, mySystem_) {

		address = new ENetAddress();
		enetEvent = new ENetEvent();

		//check if Enet was initialized
		if (enet_initialize() != 0)
		{
			std::cout << "Enet failed to initialise!" << "\n\n";
		}

		//create client
		client = enet_host_create(NULL, 1, 2, 0, 0);

		if (client == NULL)
		{
			std::cout << "Client failed to initialise!" << "\n\n";
		}

		//Set host values to local and port to 1234
		enet_address_set_host(address, "localhost");
		address->port = 1234;

		//put everything together in a peer
		peer = enet_host_connect(client, address, 2, 0);

		if (peer == NULL) {
			std::cout << "No available peers for initializing an ENet connection.\n";
		}

		serverData = new PhysicsData;
		clientData = new ClientData;
		packetType = new int;

		*packetType = -1;

		clientPacket = new ClientPacket;
		dataPacket = new ENetPacket;


		clientIndex = -1;


	};
	NetComponent(const NetComponent& other) : Component(other) {

		address = other.address;
		client = other.client;
		peer = other.peer;
		enetEvent = other.enetEvent;
		clientData = other.clientData;
		clientIndex = other.clientIndex;
		clientPacket = other.clientPacket;
		dataPacket = other.dataPacket;
		packetType = other.packetType;
		serverData = other.serverData;
	};
	~NetComponent() {

		if (peer != NULL)
		{
			enet_peer_disconnect_now(peer, 0);
		}
	};

	NetComponent& operator=(const NetComponent& other);

	void Update();

	int clientIndex;
private:
	ENetAddress* address;
	ENetHost* client;
	ENetPeer* peer;
	ENetEvent* enetEvent;
	ClientData* clientData;
	PhysicsData* serverData;
	ClientPacket* clientPacket;
	ENetPacket* dataPacket;
	int* packetType;
	
};