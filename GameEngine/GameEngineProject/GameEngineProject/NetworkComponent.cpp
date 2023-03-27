#include "NetworkComponent.h"
//#include "SFML/Graphics.hpp"
//#include "GameObject.h"
//#include "NetworkSubsystem.h"
#include "EventQueue.h"

NetworkComponent& NetworkComponent::operator=(const NetworkComponent& other)
{
	if (this == &other)
	{
		return *this;
	}

	memcpy(this, &other, sizeof(other));
	return *this;
}

void NetworkComponent::Update()
{
	

	while (enet_host_service(client, enetEvent, 0) > 0)
	{
		std::vector<GameObject*> objects;
		std::vector<SubsystemType> systems;
		int i;

		Event* event;

		switch (enetEvent->type) {



		case ENET_EVENT_TYPE_RECEIVE:

			memcpy(packetType, enetEvent->packet->data, sizeof(int));

			if (*packetType == 0)
			{
				std::cout << "Packet Received!\n";
				memcpy(clientData, enetEvent->packet->data, sizeof(ClientData));
				clientIndex = clientData->clientIndex;
			}
			else if (*packetType == 1)
			{
				memcpy(serverData, enetEvent->packet->data, sizeof(PhysicsData));
				for (int i = 0; i < 2; i++)
				{
					if (i != clientIndex)
					{						

						event = new Event();
						objects.push_back(myObject);
						systems.push_back(SubsystemType::Physics);
						event->assignObjects(objects);
						event->assignSystems(systems);
						event->type = EventType::SetPosition;
						event->positionData = b2Vec2(serverData->positions[i].x, serverData->positions[i].y);
							
					}
				}
			}

			break;
		}
	}

	clientPacket->clientIndex = clientIndex;
	clientPacket->position.x = position.x;
	clientPacket->position.y = position.y;

	dataPacket = enet_packet_create(clientPacket, sizeof(ClientPacket), ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, dataPacket);

	//enet_host_destroy(client);
	//atexit(enet_deinitialize);
}
