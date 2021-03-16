#include "spaceHell.h"

//main code for the game!
int main()
{
	srand(static_cast<unsigned>(time(0)));
	SpaceHell game;
	game.run();
	return 0;
}
