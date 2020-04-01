#pragma once
#include "BingoPlayer.h"
#include "randomc.h"

#define TOTAL_BINGO_NUMS 90
#define BINGO_START_NUM 10
#define BINGO_CARD_SIZE 9

// The Bingo Server is a Bingo player that acts as the dealer to all the client players
class BingoServer : public BingoPlayer
{
private:
	double timer = 0;
	double currentTime = 0;
	int lastDrawnIndex = 0;
	int bingoNums[TOTAL_BINGO_NUMS];
	CRandomMersenne randGen;

public:
	BingoServer();
	bool update(RakNetController& rn) override;
	void start() override;
	void processMessage(Message& message) override;
	int drawNumber();
	void shuffleBingoNums(int startIndex);
};

