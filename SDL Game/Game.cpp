#include <iostream>
#include <chrono>
#include "Game.h"
#include "Animation.h"

Game::Game()
{
	std::cout << "Game Contructor\n";
	handler = nullptr;
	window = nullptr;
	renderer = nullptr;
	running = false;
}

Game::~Game()
{
	
}

Animation* player;

void Game::Init(const char* title, Uint32 xPos, Uint32 yPos, Uint32 sWidth, Uint32 sHeight, bool fullscreen)
{
	Uint32 flags = 0;

	if (SDL_Init(SDL_INIT_EVERYTHING))
		Game::LogErr();

	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if (xPos == 0) 
		xPos = SDL_WINDOWPOS_CENTERED;
	if (yPos == 0) 
		yPos = SDL_WINDOWPOS_CENTERED;

	window = SDL_CreateWindow(title, xPos, yPos, sWidth, sHeight, flags);
	
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
		Game::LogErr();

	handler = new Handler();

	running = true;  // immediately start the game for now

	player = new Animation(renderer);
	player->CreateFrames(R"(assets\Sprites\Player\Sword\Defence0\attack.png)", 2, 2, 160, 160, 5);
}

void Game::Destroy()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Game::Update()
{
	handler->Update();
}

SDL_Rect playerPos = { 100, 100, 160, 160 };

void Game::Render(float dt)
{
	SDL_SetRenderDrawColor(renderer, 200, 200, 200, 0);
	SDL_RenderClear(renderer);

	// render code here
	SDL_RenderCopyEx(renderer, player->GetNextFrame(dt), nullptr, &playerPos, 0, nullptr, SDL_FLIP_HORIZONTAL);

	SDL_RenderPresent(renderer);
}

void Game::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			running = false;
			std::cout << "Quitting game...\n";
			break;
		case SDL_MOUSEBUTTONDOWN:
			std::cout << "Mouse pressed\n";
			break;
		case SDL_MOUSEBUTTONUP:
			std::cout << "Mouse up\n";
			break;
		default:
			break;
		}
	}
}

void Game::Run()
{
	const int TICKS_PER_SECOND = 60;
	const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
	const int MAX_FRAMESKIP = 5;

	Uint32 nextGameTick = SDL_GetTicks();
	int loops;
	float interpolation;

	while (isRunning()) {
		HandleEvents();
		loops = 0;
		while (SDL_GetTicks() > nextGameTick && loops < MAX_FRAMESKIP) {
			Update();

			nextGameTick += SKIP_TICKS;
			loops++;
		}

		interpolation = float(SDL_GetTicks() + SKIP_TICKS - nextGameTick)
			/ float(SKIP_TICKS);
		Render(interpolation);
	}
}

bool Game::isRunning()
{
	return running;
}

void Game::LogErr()
{
	std::cout << "[ERROR]: " << SDL_GetError() << '\n';
	exit(-1);
}