#include "BingoServer.h"
#include "randomc.h"
#include <iostream>
#include <sstream>
#include <conio.h>
#include <time.h>

BingoServer::BingoServer() : bingoNums{},  randGen(time(NULL))
{
	for (int i = 0; i < TOTAL_BINGO_NUMS; i++)
	{
		bingoNums[i] = BINGO_START_NUM + i;
	}
}

bool BingoServer::update(RakNetController& rn)
{ 
	std::list<Message> recMessages = rn.RecvData();
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
		//printf("%c", key);

		if (key == 32 && !gameStarted)
		{
			//StartGame();
			std::cout << "GAME STARTED!" << std::endl;
			lastDrawnIndex = 0;
			int numClients = rn.m_peerGUIDs.size();
			
			
			int clientIndex = 0;
			for (auto& guid : rn.m_peerGUIDs)
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
				rn.SendData(newMessage);

				clientIndex++;
			}
			gameStarted = true;
			shuffleBingoNums(0);
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

		if (timer > 1000)
		{
			// All possible bingo nums have been drawn (should never happen)
			if (lastDrawnIndex >= TOTAL_BINGO_NUMS)
			{
				std::cout << "No more numbers to draw! Someone should have won by now..." << std::endl;
				//EndGame();
			}
			else
			{
				int drawNum = drawNumber();
				RakNet::MessageID messageID = (RakNet::MessageID) ID_NUMBER_DRAWN;
				for (auto& guid : rn.m_peerGUIDs)
				{
					Message newMessage(messageID, guid, std::to_string(drawNum));
					rn.SendData(newMessage);
				}
			}

			timer = 0;
		}
	}

	return true;

	//while ((key != '\r') && (key != 27))
	//{
	//	if (!gameStarted)
	//	{

	//	}

	//	if (_kbhit())
	//	{
	//		key = _getch();
	//		ss << key;
	//		printf("%c", key);
	//	}
	//	rn.RecvData();
	//}
	//if (key == 27)
	//	break;

	//rn.SendData(ss.str().c_str());
}

void BingoServer::start()
{
	std::cout << "Welcome to Bingo!" << std::endl;
	std::cout << "You are the dealer!" << std::endl << std::endl;
	std::cout << "Ready?\n\n Start Game [Space]    End [Esc]" << std::endl;
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
	case ID_BINGO_WINNER:
		std::cout << "We have a winner!" << std::endl;
		//EndGame()
		gameStarted = false;
		break;
	default:
		std::cout << "I can't do anything with this message (ID: " << message.id << std::endl;
	}
}
