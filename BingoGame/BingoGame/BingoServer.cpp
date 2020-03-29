#include "BingoServer.h"
#include "randomc.h"
#include <iostream>
#include <sstream>
#include <conio.h>
#include <time.h>

bool BingoServer::update(RakNetController& rn)
{
	currentTime = GetTickCount();
	rn.RecvData();

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
			gameStarted = true;
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
			int drawNum = drawNumber();
			RakNet::MessageID messageID = (RakNet::MessageID) ID_NUMBER_DRAWN;
			Message newMessage(messageID, rn.m_peerGUID, std::to_string(drawNum));
			rn.SendData(newMessage);
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
	CRandomMersenne randGen = CRandomMersenne(time(NULL));
	int randNum = randGen.IRandomX(10, 99);
	std::cout << randNum << " was drawn." << std::endl;

	return randNum;
}
