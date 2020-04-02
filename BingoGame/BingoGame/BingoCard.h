#pragma once
#include <vector>
#include <set>
#include <list>
#include <iostream>

#define BINGO_CARD_NUM_ROWS 3
#define BINGO_CARD_NUM_COLS 3
#define TOTAL_BINGO_NUMS 90
#define BINGO_START_NUM 10
#define BINGO_CARD_SIZE 9

class BingoCard
{

// Members

private:
	std::vector<int> cardNumbers;
	std::set<int> markedNumbers;

// Methods

public:
	void fillCard(std::list<int>& nums);
	bool markNumber(int num);
	void printCard();
	bool checkCardCompleted();
};

