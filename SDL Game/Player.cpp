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
	mousePosX = 0;
	mousePosY = 0;
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
	float newPosX = posX + speedX;
	float newPosY = posY + speedY;

	if (newPosX - sizeX/2 > 0 && newPosX + sizeX/2 < Game::WINDOW_WIDTH)
		posX = newPosX;
	if (newPosY - sizeY/2 > 0 && newPosY + sizeY/2  < Game::WINDOW_HEIGHT)
		posY = newPosY;
}


void Player::Render(float dt)
{
	float posXAux = posX + speedX * dt;
	float posYAux = posY + speedY * dt;

	SDL_Rect playerPos = { (int)(posXAux - sizeX / 2), (int)(posYAux - sizeY / 2), (int)sizeX, (int)sizeY };
	SDL_Rect pos = { 0, 0, (int)sizeX, (int)sizeY };

	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (posX > mousePosX)
		flip = SDL_FLIP_HORIZONTAL;

	SDL_RenderCopyEx(renderer, GetTex(), &pos, &playerPos, 0, nullptr, flip);
}

float Player::GetPosX()
{
	return posX;
}

float Player::GetPosY()
{
	return posY;
}

float Player::GetSizeX()
{
	return sizeX;
}

float Player::GetSizeY()
{
	return sizeY;
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

void Player::SetMousePos(int x, int y)
{
	mousePosX = x;
	mousePosY = y;
}

void Player::FireProj(int xCoord, int yCoord)
{
	//double theta = atan(((float)yCoord - yPlayer) / ((float)xCoord - xPlayer));

	//if (xCoord < xPlayer)
	//	theta += M_PI;

	//handler->AddObj(new Projectile(renderer, xPlayer, yPlayer, 30, 30, (float)(10 * cos(theta)), (float)(10 * sin(theta)), R"(assets\Sprites\Bows\fire_arrow.png)"));
	//std::cout << "Coords: " << cos(theta) << ' ' << sin(theta) << '\n';
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
