#pragma once
#include "BingoPlayer.h"
#include "BingoCard.h"

// A Bingo client is a Bingo player that competes to win the Bingo game
class BingoClient : public BingoPlayer
{
	RakNet::AddressOrGUID serverGUID;
	BingoCard bingoCard;

public:
	bool update(RakNetController& rn) override;
	void start() override;
	void processMessage(Message& message) override;
};

