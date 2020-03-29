#include "BingoGame.h"
	
int main(int argc, char* argv[])
{
	BingoGame bingoGame = BingoGame();
	int retValue = bingoGame.initialize(argc, argv);

	if (retValue == 0)
	{
		bingoGame.gameLoop();
		bingoGame.cleanup();
	}
	return retValue;
}