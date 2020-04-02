#include<sstream>
#include<iostream>
#include<stdio.h>
#include<conio.h>
#include "BingoGame.h"
#include "BingoServer.h"
#include "BingoClient.h"

int BingoGame::initialize(int argc, char* argv[])
{
	if (argc == 1)
	{
		return -1;
	}

	rn = new RakNetController();

	if (strcmp(argv[1], "server") == 0)
	{
		if ((!rn->Initialize()) || (!rn->CreateServer(27015)))
		{
			return -1;
		}
		bingoPlayer = new BingoServer();
	}
	else if (strcmp(argv[1], "client") == 0)
	{
		if ((!rn->Initialize()) || (!rn->CreateClient("127.0.0.1", 27015)))
		{
			return -1;
		}
		bingoPlayer = new BingoClient();
	}
	else return -1;

	bingoPlayer->rn = rn;

	return 0;
}

void BingoGame::gameLoop()
{
	if (bingoPlayer == nullptr)
	{
		return;
	}

	bingoPlayer->start();

	while (true)
	{
		if (!bingoPlayer->update())
		{
			break;
		}
	}
}

void BingoGame::cleanup()
{
	rn->Cleanup();
	delete bingoPlayer;
	delete rn;
}
