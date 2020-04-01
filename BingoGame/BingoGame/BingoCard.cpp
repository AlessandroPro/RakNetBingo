#include "BingoCard.h"

void BingoCard::fillCard(std::list<int>& nums)
{
	int totalBingoNums = BINGO_CARD_NUM_ROWS * BINGO_CARD_NUM_COLS;
	
	cardNumbers.clear();
	markedNumbers.clear();

	for (auto& num : nums)
	{
		// if the bingo card is full
		if (cardNumbers.size() >= totalBingoNums)
		{
			break;
		}

		cardNumbers.push_back(num);
	}
}

bool BingoCard::markNumber(int num)
{
	for (auto& cardNum : cardNumbers)
	{
		if (cardNum == num)
		{
			markedNumbers.emplace(num);
			return true;
		}
	}
	return false;
}

void BingoCard::printCard()
{
	std::cout << std::endl;
	std::cout << "My Bingo Card: " << markedNumbers.size() << std::endl << std::endl;
	for (int i = 0; i < BINGO_CARD_NUM_ROWS; i++)
	{
		for (int j = 0; j < BINGO_CARD_NUM_COLS; j++)
		{
			int numIndex = (i * BINGO_CARD_NUM_COLS) + j;
			if (markedNumbers.find(cardNumbers[numIndex]) != markedNumbers.end())
			{
				// This number has been marked, so print an O in its place
				std::cout << "O ";
			}
			else
			{
				// This number has not been marked, so print it
				std::cout << cardNumbers[numIndex];
			}

			std::cout << "  ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool BingoCard::checkCardCompleted()
{
	if (cardNumbers.size() == markedNumbers.size())
	{
		// The card is fully marked
		return true;
	}
	return false;
}
