#pragma once
#include "BingoPlayer.h"
#include "randomc.h"
#include "BingoCard.h"

#define DRAW_TIME_MS 100

// The Bingo Server is a Bingo player that acts as the dealer to all the client players
class BingoServer : public BingoPlayer
{
private:
	double timer = 0;
	double currentTime = 0;
	int lastDrawnIndex = 0;
	int bingoNums[TOTAL_BINGO_NUMS];
	std::set<RakNet::RakNetGUID> clientPlayers;
	CRandomMersenne randGen;

public:
	BingoServer();
	bool update() override;
	void startGame() override;
	void start() override;
	void processMessage(Message& message) override;
	int drawNumber();
	void shuffleBingoNums(int startIndex);
};

