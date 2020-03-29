#pragma once

#include <WinSock2.h>
#include <string>

#include "RakPeerInterface.h"
#include <list>

struct Message
{
	RakNet::MessageID id;
	RakNet::AddressOrGUID peerGUID;
	std::string data;

	Message(RakNet::MessageID _id, RakNet::AddressOrGUID _peerGUID, std::string _data) :
		id(_id), peerGUID(_peerGUID), data(_data) {}
};

class RakNetController
{
// Members
private:
	RakNet::RakPeerInterface* m_peer = NULL;
	bool m_isServer;

public:
	RakNet::AddressOrGUID m_peerGUID;

//Methods
public:
	bool Initialize();
	void Cleanup();
	bool CreateServer(int _serverPort);
	bool CreateClient(std::string _serverIP, int _serverPort);
	bool SendData(Message& message);
	std::list<Message> RecvData();
};

