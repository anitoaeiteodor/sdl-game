#include <iostream>
#include <chrono>
#include "Game.h"
#include "Animation.h"
#include "Player.h"

int Game::WINDOW_HEIGHT;
int Game::WINDOW_WIDTH;

Player* player;

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

void Game::Init(const char* title, Uint32 xPos, Uint32 yPos, Uint32 sWidth, Uint32 sHeight, bool fullscreen)
{
	WINDOW_HEIGHT = sHeight;
	WINDOW_WIDTH = sWidth;

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

	player = new Player(renderer, 200, 200, 160, 160);
}

void Game::Destroy()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Game::Update()
{
	handler->Update();
	player->Update();
}

SDL_Rect playerPos = { 100, 100, 160, 160 };

void Game::Render(float dt)
{
	SDL_SetRenderDrawColor(renderer, 200, 200, 200, 0);
	SDL_RenderClear(renderer);

	// render code here
	player->Render(dt);

	SDL_RenderPresent(renderer);
}

void Game::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		const Uint8* keys = SDL_GetKeyboardState(nullptr);
		int speedX = 0;
		int speedY = 0;

		if (keys[SDL_SCANCODE_A])
			speedX -= 10;
		if (keys[SDL_SCANCODE_D])
			speedX += 10;
		if (keys[SDL_SCANCODE_W])
			speedY -= 10;
		if (keys[SDL_SCANCODE_S])
			speedY += 10;

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

		player->SetSpeed(speedX, speedY);
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