#pragma once
#include "BingoPlayer.h"

// The Bingo Server is a Bingo player that acts as the dealer to all the client players
class BingoServer : public BingoPlayer
{
private:
	double timer = 0;
	double currentTime = 0;

public:
	bool update(RakNetController& rn) override;
	void start() override;
	int drawNumber();
};

