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
	player->CreateFrames(R"(assets\Sprites\Player\Sword\Defence0\walk.png)", 2, 2, 160, 160, 300);
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
	SDL_RenderCopy(renderer, player->GetNextFrame(dt), nullptr, &playerPos);

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

void Game::LogErr()
{
	std::cout << "[ERROR]: " << SDL_GetError() << '\n';
	exit(-1);
}