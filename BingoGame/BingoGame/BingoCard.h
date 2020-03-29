#pragma once
#include <map>
#include <vector>

#define NUM_ROWS 3
#define NUM_COLS 3

class BingoCard
{

// Members

private:
	int const minNum = 10;
	int const maxNum = 99;

	std::vector<int> numbers;
	std::map<int, int> unmarkedNumbers;

// Methods

public:
	void fillCard();
	void fillCard(std::vector<int>& nums);
	bool checkNumber(int num);
};

