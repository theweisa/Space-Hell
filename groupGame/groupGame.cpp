#include "game.h"

int main()
{
	srand(static_cast<unsigned>(time(0)));
	Game game;
	game.run();
	return 0;
}