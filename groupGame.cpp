#include "game.h"

//main code for the game!
int main()
{
	srand(static_cast<unsigned>(time(0)));
	bool gameReset;
	/**
	do {
		Game *game = new Game();
		gameReset = game->run();
		std::cout << "GameReset" << gameReset << std::endl;
		delete game;s

	}while (gameReset != true);
	*/
	Game game;
	game.run();
	return 0;
}