#include "Player.h"
#include "TextureManager.h"

Player::Player(SDL_Renderer* rend, int posX, int posY, int sizeX, int sizeY)
{
	renderer = rend;
	this->posX = posX;
	this->posY = posY;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	speedX = 0;
	speedY = 0;
	tex = TextureManager::LoadTexture(R"(assets\Sprites\Player\Sword\Defence0\idle.png)", renderer);
}

Player::~Player()
{
	SDL_DestroyTexture(tex);
}

GameObjID Player::GetID()
{
	return id;
}

void Player::Update()
{
	int newPosX = posX + speedX;
	int newPosY = posY + speedY;

	if (newPosX - sizeX/2 > 0 && newPosX + sizeX/2 < Game::WINDOW_WIDTH)
		posX = newPosX;
	if (newPosY - sizeY/2 > 0 && newPosY + sizeY/2 < Game::WINDOW_HEIGHT)
		posY = newPosY;
}

void Player::Render(float dt)
{
	SDL_Rect playerPos = { posX - sizeX/2, posY - sizeY/2, sizeX, sizeY };
	SDL_Rect pos = { 0, 0, 160, 160 };
	SDL_RenderCopy(renderer, tex, &pos, &playerPos);
}

void Player::SetSpeed(int speedX, int speedY)
{
	this->speedX = speedX;
	this->speedY = speedY;
}
