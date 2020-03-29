#pragma once
#include "RakNetController.h"
#include"MessageIdentifiers.h"

class BingoPlayer
{
protected:
	bool gameStarted = false;

public:
	virtual bool update(RakNetController& rn);
	virtual void start();
	virtual void processMessage(Message& message);
};

enum BingoMessageIDTypes
{
	ID_NUMBER_DRAWN = ID_USER_PACKET_ENUM + 1,
	ID_BINGO_CARD_CREATED,
};

