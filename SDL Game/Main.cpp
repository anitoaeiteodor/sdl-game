#include <SDL.h>
#include <iostream>
#include "Game.h"

int main(int argc, char* argv[])
{
	Game game;
	game.Init("Game", 0, 0, 800, 600, false);
	game.Run();
	game.Destroy();
	return 0;
}