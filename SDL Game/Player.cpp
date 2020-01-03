#include "Player.h"
#include "TextureManager.h"
#include <iostream>

Player::Player(SDL_Renderer* rend, float posX, float posY, float sizeX, float sizeY)
{
	renderer = rend;
	this->posX = posX;
	this->posY = posY;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	speedX = 0;
	speedY = 0;
	CreateAnimationSystem();
}

Player::~Player()
{
}

GameObjID Player::GetID()
{
	return id;
}

void Player::Update()
{
	if (speedX || speedY)
	{
		anSys->ProcessInput(Command::RUN);
		//std::cout << "Running\n";
	}
	else
	{
		anSys->ProcessInput(Command::IDLE);
		//std::cout << "Idle\n";
	}
	int newPosX = posX + speedX;
	int newPosY = posY + speedY;

	if (newPosX - sizeX/2 > 0 && newPosX + sizeX/2 < Game::WINDOW_WIDTH)
		posX = newPosX;
	if (newPosY - sizeY/2 > 0 && newPosY + sizeY/2  < Game::WINDOW_HEIGHT)
		posY = newPosY;
}

SDL_RendererFlip prevFlip;

void Player::Render(float dt)
{
	SDL_Rect playerPos = { posX - sizeX/2, posY - sizeY/2, sizeX, sizeY };
	SDL_Rect pos = { 0, 0, 160, 160 };
	if (speedX > 0)
	{
		SDL_RenderCopyEx(renderer, GetTex(), &pos, &playerPos, 0, nullptr, SDL_FLIP_NONE);
		prevFlip = SDL_FLIP_NONE;
	}
	else if (speedX < 0)
	{
		SDL_RenderCopyEx(renderer, GetTex(), &pos, &playerPos, 0, nullptr, SDL_FLIP_HORIZONTAL);
		prevFlip = SDL_FLIP_HORIZONTAL;
	}
	else 
		SDL_RenderCopyEx(renderer, GetTex(), &pos, &playerPos, 0, nullptr, prevFlip);
}

float Player::GetPosX()
{
	return posX;
}

float Player::GetPosY()
{
	return posY;
}

bool Player::CheckCollision(GameObj* other)
{
	return false;
}

void Player::SetSpeed(float speedX, float speedY)
{
	this->speedX = speedX;
	this->speedY = speedY;
}

SDL_Texture* Player::GetTex()
{
	return anSys->GetNextFrame();
}

void Player::CreateAnimationSystem()
{
	// temporary
	Animation* idle = new Animation(renderer);
	Animation* run = new Animation(renderer);
	idle->CreateFrames(R"(assets\Sprites\Player\idle\idle_def_0.png)", 2, 2, 160, 160, 10);
	run->CreateFrames(R"(assets\Sprites\Player\walk\walk_def_0.png)", 2, 2, 160, 160, 10);
	
	anSys = new AnimationSystem(2);
	anSys->AddAnimation(idle);
	anSys->AddAnimation(run);
	
	anSys->AddTrigger(0, 1, Command::RUN);
	anSys->AddTrigger(1, 1, Command::RUN);
	anSys->AddTrigger(0, 0, Command::IDLE);
	anSys->AddTrigger(1, 0, Command::IDLE);
}
