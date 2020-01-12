#include <SDL.h>
#include <iostream>
#include "Game.h"

int main(int argc, char* argv[])
{
	Game game;
	game.Init("Game", 0, 0, 1280, 720, false);
	game.Run();
	game.Destroy();
	return 0;
}