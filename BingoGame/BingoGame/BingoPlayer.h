#pragma once
#include "RakNetController.h"
#include"MessageIdentifiers.h"

class BingoPlayer
{

// Members
protected:
	bool gameStarted = false;

public:
	RakNetController* rn;

// Methods
public:
	virtual bool update();
	virtual void startGame();
	virtual void start();
	virtual void processMessage(Message& message);
	virtual ~BingoPlayer();
};

enum BingoMessageIDTypes
{
	ID_NUMBER_DRAWN = ID_USER_PACKET_ENUM + 1,
	ID_BINGO_CARD_CREATED,
	ID_BINGO_CARD_COMPLETED, 
	ID_BINGO_GAME_START,
	ID_BINGO_GAME_END
};

