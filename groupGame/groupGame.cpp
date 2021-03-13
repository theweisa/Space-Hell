#include "game.h"

int main()
{
	srand(static_cast<unsigned>(time(0)));
	bool gameReset;
	/**
	do {
		Game *game = new Game();
		gameReset = game->run();
		std::cout << "GameReset" << gameReset << std::endl;
		delete game;

	}while (gameReset != true);
	*/
	Game game;
	game.run2();
	return 0;
}