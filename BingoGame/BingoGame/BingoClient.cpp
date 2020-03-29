#include "BingoClient.h"
#include <iostream>

bool BingoClient::update(RakNetController& rn)
{
	std::list<Message> recMessages = rn.RecvData();
	for (auto& message : recMessages)
	{
		processMessage(message);
	}
	return true;
}

void BingoClient::start()
{
}

void BingoClient::processMessage(Message& message)
{
	switch (message.id)
	{
	case ID_NUMBER_DRAWN:
		std::cout << "Marking " + message.data << std::endl;
		break;
	default:
		std::cout << "I can't do anything with this message (ID: " << message.id << std::endl;
	}

}
