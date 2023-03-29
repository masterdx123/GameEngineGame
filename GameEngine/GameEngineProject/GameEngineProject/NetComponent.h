#pragma once

#include "Component.h"
#include <enet\enet.h>
#include "EventQueue.h"



struct PhysicsData {
	int packetType = 1;
	Vector2 positions[2];
};

struct ClientData {
	int packetType = 0;
	int clientIndex;
};

struct ClientPacket {
	int clientIndex;
	Vector2 position;
};

class NetComponent : public Component {
public:
	NetComponent(GameObject* myObject_, Subsystem* mySystem_) : Component(ComponentType::Network, myObject_, mySystem_) {

		address = new ENetAddress();
		enetEvent = new ENetEvent();
		if (enet_initialize() != 0)
		{
			std::cout << "Enet failed to initialise!" << "\n\n";
		}


		client = enet_host_create(NULL, 1, 2, 0, 0);

		if (client == NULL)
		{
			std::cout << "Client failed to initialise!" << "\n\n";
		}

		enet_address_set_host(address, "localhost");
		address->port = 1234;

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