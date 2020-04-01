#pragma once
#include <vector>
#include <set>
#include <list>
#include <iostream>

#define BINGO_CARD_NUM_ROWS 3
#define BINGO_CARD_NUM_COLS 3

class BingoCard
{

// Members

private:
	int const minNum = 10;
	int const maxNum = 99;

	std::vector<int> cardNumbers;
	std::set<int> markedNumbers;

// Methods

public:
	void fillCard(std::list<int>& nums);
	bool markNumber(int num);
	void printCard();
	bool checkCardCompleted();
};

