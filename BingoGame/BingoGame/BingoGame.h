#pragma once
#include "BingoPlayer.h"
#include "RakNetController.h"

class BingoGame
{

// Members
private:
	BingoPlayer* bingoPlayer;
	RakNetController* rn;

// Methods

public:
	int initialize(int argc, char* argv[]);
	void gameLoop();
	void cleanup();
};

