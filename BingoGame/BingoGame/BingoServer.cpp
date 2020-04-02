#include "BingoServer.h"
#include "randomc.h"
#include <iostream>
#include <sstream>
#include <conio.h>
#include <time.h>

BingoServer::BingoServer() : bingoNums{}, clientPlayers(), randGen(time(NULL))
{
	clientPlayers.clear();
	for (int i = 0; i < TOTAL_BINGO_NUMS; i++)
	{
		bingoNums[i] = BINGO_START_NUM + i;
	}
}

bool BingoServer::update()
{ 
	std::list<Message> recMessages = rn->RecvData();
	for (auto& message : recMessages)
	{
		processMessage(message);
	}

	currentTime = GetTickCount();
	char key = ' ';
	std::stringstream ss;

	if (_kbhit())
	{
		key = _getch();
		ss << key;

		if (key == 's' && !gameStarted)
		{
			if ((rn->m_peerGUIDs).size() > 0)
			{
				startGame();
			}
			else
			{
				std::cout << "We need at least 1 player to begin!" << std::endl;
			}
		}
		else if (key == 27)
		{
			//EndGame();
			return false;
		}
	}

	if (gameStarted)
	{
		double deltaTime = GetTickCount() - currentTime;
		timer += deltaTime;

		if (timer > DRAW_TIME_MS)
		{
			// All possible bingo nums have been drawn (should never happen)
			if (lastDrawnIndex >= TOTAL_BINGO_NUMS)
			{
				std::cout << "No more numbers to draw! Someone should have won by now..." << std::endl << std::endl;
				gameStarted = false;
				start();
			}
			else
			{
				int drawNum = drawNumber();
				RakNet::MessageID messageID = (RakNet::MessageID) ID_NUMBER_DRAWN;
				for (auto& guid : clientPlayers)
				{
					Message newMessage(messageID, guid, std::to_string(drawNum));
					rn->SendData(newMessage);
				}
			}

			timer = 0;
		}
	}

	return true;
}

void BingoServer::startGame()
{
	lastDrawnIndex = 0;
	clientPlayers.clear();
	for (auto& guid : rn->m_peerGUIDs)
	{
		clientPlayers.emplace(guid);
	}
	int numClients = clientPlayers.size();

	std::cout << "GAME STARTED!" << std::endl;
	std::cout << "Number of players: " << numClients << std::endl;

	// Generate and send bingo card nubmers for client
	int clientIndex = 0;
	for (auto& guid : clientPlayers)
	{
		std::string bingoCardNumList = "";
		bingoCardNumList += std::to_string(bingoNums[clientIndex]) + ":";
		shuffleBingoNums(numClients);
		for (int i = 0; i < BINGO_CARD_SIZE - 1; i++)
		{
			int nextBingoNum = bingoNums[numClients + i];
			bingoCardNumList += std::to_string(nextBingoNum) + ":";
		}

		RakNet::MessageID messageID = (RakNet::MessageID) ID_BINGO_CARD_CREATED;
		Message newMessage(messageID, guid, bingoCardNumList);
		rn->SendData(newMessage);

		clientIndex++;
	}
	gameStarted = true;
	shuffleBingoNums(0);
}

void BingoServer::start()
{
	std::cout << "Welcome to Bingo!" << std::endl;
	std::cout << "You are the dealer!" << std::endl << std::endl;
	std::cout << "Ready?\n\n Start Game [s]    End [Esc]" << std::endl;
}

int BingoServer::drawNumber()
{
	int drawnNum = bingoNums[lastDrawnIndex];
	std::cout << drawnNum << " was drawn." << std::endl;
	lastDrawnIndex++;

	return drawnNum;
}

void BingoServer::shuffleBingoNums(int startIndex)
{
	if (startIndex >= TOTAL_BINGO_NUMS)
	{
		return;
	}

	// Swaps each bingo num with another randomly selected bingo num
	// The bingo nums before the startIndex are untouched
	for (int i = startIndex; i < TOTAL_BINGO_NUMS; i++)
	{
		int randIndex = randGen.IRandomX(startIndex, TOTAL_BINGO_NUMS - 1);
		int tempNum = bingoNums[i];
		bingoNums[i] = bingoNums[randIndex];
		bingoNums[randIndex] = tempNum;
	}
}

void BingoServer::processMessage(Message& message)
{
	switch (message.id)
	{
		case ID_BINGO_CARD_COMPLETED:
		{
			if (!gameStarted)
			{
				break;
			}
			std::cout << "We have a winner!" << std::endl;
			std::cout << "The game has ended." << std::endl;
			gameStarted = false;

			for (auto& guid : clientPlayers)
			{
				RakNet::MessageID messageID = (RakNet::MessageID) ID_BINGO_GAME_END;
				std::string winnerMessage;
				if (guid == message.peerGUID)
				{
					winnerMessage = "You are the Winner!!";
				}
				else
				{
					winnerMessage = "You lost...";
				}
				Message newMessage(messageID, guid, winnerMessage);
				rn->SendData(newMessage);
			}
			break;
		}
		default:
			std::cout << "I can't do anything with this message (ID: " << message.id << std::endl;
	}
}
