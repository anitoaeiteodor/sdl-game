#include <iostream>
#include <chrono>
#include "Game.h"
#include "Animation.h"
#include "Player.h"
#include "Arrow.h"

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

	// testing code after this line

	running = true;  // immediately start the game for now

	player = new Player(renderer, { 200, 200 }, { 160, 160 });
	handler->AddObj(player);
	//handler->AddObj(new Projectile(renderer, 0, 0, 30, 80, 5, 5, R"(assets\Sprites\Bows\fire_arrow.png)"));
}

void Game::Destroy()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	if (handler)
	{
		delete handler;
		handler = 0;
	}
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
	handler->Render(dt);

	SDL_RenderPresent(renderer);
}

void Game::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		const Uint8* keys = SDL_GetKeyboardState(nullptr);
		float speedX = 0;
		float speedY = 0;

		int xCoord, yCoord;
		SDL_GetMouseState(&xCoord, &yCoord);
		Vector2D mousePos = { xCoord, yCoord };
		player->SetMousePos(mousePos);

		if (keys[SDL_SCANCODE_A])
			speedX -= 5;
		if (keys[SDL_SCANCODE_D])
			speedX += 5;
		if (keys[SDL_SCANCODE_W])
			speedY -= 5;
		if (keys[SDL_SCANCODE_S])
			speedY += 5;

		switch (event.type)
		{
		case SDL_QUIT:
			running = false;
			std::cout << "Quitting game...\n";
			break;
		case SDL_MOUSEBUTTONDOWN:
			{
				std::cout << "Mouse pressed\n";

				Vector2D playerPos = player->GetPos();

				handler->AddObj(new Arrow(renderer, { 30.0f, 80.0f }, { playerPos.x, playerPos.y }, { (float)xCoord, (float)yCoord }, 20.0f, R"(assets\Sprites\Bows\regular_arrow.png)"));
				//std::cout << "Coords: " << cos(theta) << ' ' << sin(theta) << '\n';
				break;
			}
		case SDL_MOUSEBUTTONUP:
			//std::cout << "Mouse up\n";
			break;
		default:
			break;
		}

		player->SetSpeed({ speedX, speedY });
	}
}

void Game::Run()
{
	const Uint32 TICKS_PER_SECOND = 60;
	const Uint32 SKIP_TICKS = 1000 / TICKS_PER_SECOND;
	const Uint32 MAX_FRAMESKIP = 5;

	Uint32 nextGameTick = SDL_GetTicks();
	Uint32 loops;
	float interpolation;

	while (isRunning()) 
	{
		HandleEvents();
		loops = 0;
		while (SDL_GetTicks() > nextGameTick && loops < MAX_FRAMESKIP) 
		{
			Update();

			nextGameTick += SKIP_TICKS;
			loops++;
		}

		interpolation = float(SDL_GetTicks() + SKIP_TICKS - nextGameTick) / float(SKIP_TICKS);
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