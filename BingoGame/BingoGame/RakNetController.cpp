#include"RakNetController.h"
#include"MessageIdentifiers.h"
#include"RakNetTypes.h"
#include"BitStream.h"
#include <list>

bool RakNetController::Initialize() 
{ 
	m_peer = RakNet::RakPeerInterface::GetInstance(); 
	if (!m_peer)
	{ 
		return false; 
	}
	return true; 
}

void RakNetController::Cleanup()
{
	RakNet::RakPeerInterface::DestroyInstance(m_peer);
}

bool RakNetController::CreateServer(int _serverPort) 
{ 
	m_isServer = true; 
	RakNet::SocketDescriptor sd(_serverPort, 0); 
	if (m_peer->Startup(8, &sd, 1) != RakNet::RAKNET_STARTED) 
	{ 
		printf("Server failed to connect.\n"); 
		return false; 
	}
	m_peer->SetMaximumIncomingConnections(8); 
	printf("Server started.\n"); 
	return true; 
}

bool RakNetController::CreateClient(std::string _serverIP, int _serverPort) 
{ 
	m_isServer = false; 
	RakNet::SocketDescriptor sd; 

	if (m_peer->Startup(1, &sd, 1) != RakNet::RAKNET_STARTED) 
	{ 
		printf("Client failed to start up.\n"); 
		return false; 
	}

	if (m_peer->Connect(_serverIP.c_str(), _serverPort, 0, 0) != RakNet::CONNECTION_ATTEMPT_STARTED) 
	{ 
		printf("Client failed to connect.\n"); 
		return false; 
	}

	printf("Client started.\n"); 
	return true; 
}

bool RakNetController::SendData(Message& message) 
{ 
	if (message.id <= ID_USER_PACKET_ENUM)
	{
		return false;
	}
	 
	RakNet::BitStream bsOut; 
	bsOut.Write((RakNet::MessageID)(message.id)); 
	bsOut.Write(message.data.c_str()); 
	m_peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, message.peerGUID, false); 

	//printf("\nMessage sent\n"); 
	return true;
}

// Processes default messages and returns a lsit of any custom messages
std::list<Message> RakNetController:: RecvData()
{
	std::list<Message> customRecvMessages;

	for (RakNet::Packet* packet = m_peer->Receive(); packet;
		m_peer->DeallocatePacket(packet), packet = m_peer->Receive())
	{
		// Handling custom message types
		if (packet->data[0] > ID_USER_PACKET_ENUM)
		{
			RakNet::RakString rs;
			RakNet::BitStream bsIn(packet->data, packet->length, false);
			bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
			bsIn.Read(rs);

			Message newMessage(packet->data[0], packet->guid, std::string(rs.C_String()));
			customRecvMessages.push_back(newMessage);

			continue;
		}

		// Handling default message types
		switch (packet->data[0])
		{
			case ID_REMOTE_CONNECTION_LOST:
				printf("Another client has lost the connection.\n");
				break;
			case ID_REMOTE_NEW_INCOMING_CONNECTION:
				printf("Another client has connected.\n");
				break;
			case ID_CONNECTION_REQUEST_ACCEPTED:
				printf("Our connection request has been accepted.\n");
				m_peerGUIDs.emplace(packet->guid);
				break;
			case ID_NEW_INCOMING_CONNECTION:
				printf("A connection is incoming.\n");
				m_peerGUIDs.emplace(packet->guid);
				break;
			case ID_NO_FREE_INCOMING_CONNECTIONS:
				printf("The server is full.\n");
				break;
			case ID_DISCONNECTION_NOTIFICATION:
				m_peerGUIDs.erase(packet->guid);
				if (m_isServer)
					printf("A client has disconnected.\n");
				else
					printf("We have been disconnected.\n");
				break;
			case ID_CONNECTION_LOST:
				m_peerGUIDs.erase(packet->guid);
				if (m_isServer)
					printf("A client lost the connection.\n");
				else
					printf("Connection lost.\n");
				break;
			default:
				printf("Message with default identifier %i has arrived.\n", packet->data[0]); 
				break;
		}
	}
	return customRecvMessages;
}
