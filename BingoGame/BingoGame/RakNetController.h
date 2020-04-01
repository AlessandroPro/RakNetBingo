#pragma once

#include <WinSock2.h>
#include <string>

#include "RakPeerInterface.h"
#include <list>
#include <set>

struct Message
{
	RakNet::MessageID id;
	RakNet::RakNetGUID peerGUID;
	std::string data;

	Message(RakNet::MessageID _id, RakNet::RakNetGUID _peerGUID, std::string _data) :
		id(_id), peerGUID(_peerGUID), data(_data) {}
};

class RakNetController
{
// Members
private:
	RakNet::RakPeerInterface* m_peer = NULL;
	bool m_isServer;

public:
	std::set<RakNet::RakNetGUID> m_peerGUIDs;

//Methods
public:
	bool Initialize();
	void Cleanup();
	bool CreateServer(int _serverPort);
	bool CreateClient(std::string _serverIP, int _serverPort);
	bool SendData(Message& message);
	std::list<Message> RecvData();
};

