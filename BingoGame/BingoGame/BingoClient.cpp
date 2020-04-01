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
	std::cout << "Welcome to Bingo!" << std::endl;
	std::cout << "You are one of the players." << std::endl;
}

void BingoClient::processMessage(Message& message)
{
	switch (message.id)
	{
		case ID_NUMBER_DRAWN:
			std::cout <<  message.data << " called!";
			if (bingoCard.markNumber(std::stoi(message.data)))
			{
				std::cout << " That number is on my card!" << std::endl;
				bingoCard.printCard();
				if (bingoCard.checkCardCompleted())
				{
					std::cout << "My card is full!" << std::endl;
					std::cout << "I'M THE WINNER!" << std::endl;
				}
			}
			else
			{
				std::cout << " I don't have it..." << std::endl;
			}
			break;
		case ID_BINGO_CARD_CREATED:
		{
			std::cout << message.data << std::endl;
			std::list<int> bingoCardNums = parseBingoNums(message.data);
			bingoCard.fillCard(bingoCardNums);
			bingoCard.printCard();
			break;
		}
		default:
			std::cout << "I can't do anything with this message (ID: " << message.id << std::endl;
	}

}

std::list<int> BingoClient::parseBingoNums(std::string& bingoNums)
{
	std::list<int> bingoCardNums;
	std::string bingoNumString = bingoNums;
	std::string delimiter = ":";

	size_t pos = 0;
	std::string token;
	while ((pos = bingoNumString.find(delimiter)) != std::string::npos) {
		token = bingoNumString.substr(0, pos);
		bingoCardNums.push_back(std::stoi(token));
		//std::cout << token << std::endl;
		bingoNumString.erase(0, pos + delimiter.length());
	}
	return bingoCardNums;
}
