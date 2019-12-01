#include <iostream>
#include <chrono>
#include "Game.h"

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
	Uint32 flags = 0;

	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		std::cout << "[ERROR]: Something unexpected happened. " << SDL_GetError() << '\n';
		exit(-1);
	}

	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if (xPos == 0) 
		xPos = SDL_WINDOWPOS_CENTERED;
	if (yPos == 0) 
		yPos = SDL_WINDOWPOS_CENTERED;

	window = SDL_CreateWindow(title, xPos, yPos, sWidth, sHeight, flags);
	renderer = SDL_CreateRenderer(window, -1, 0);

	running = true;  // immediately start the game for now
}

void Game::Destroy()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Game::Update()
{
}

void Game::Render(float dt)
{
	SDL_SetRenderDrawColor(renderer, 200, 200, 200, 0);
	SDL_RenderClear(renderer);

	// render code here


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
	using namespace std::chrono_literals;
	using clock = std::chrono::high_resolution_clock;
	using std::chrono::nanoseconds;

	nanoseconds const timestep(1ms); // fixed timestep
	nanoseconds lag(0ns);
	auto timeStart = clock::now();

	while (isRunning()) {
		auto deltaTime = clock::now() - timeStart;
		timeStart = clock::now();
		lag += std::chrono::duration_cast<nanoseconds>(deltaTime);

		HandleEvents();

		// update game logic as lag permits
		while (lag >= timestep) {
			lag -= timestep;
			Update(); // update at a fixed rate each time
		}

		// calculate how close or far we are from the next timestep
		auto alpha = (float)lag.count() / timestep.count();
		Render(alpha);
	}
}

bool Game::isRunning()
{
	return running;
}
