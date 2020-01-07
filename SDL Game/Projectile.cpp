#include "Projectile.h"
#include "TextureManager.h"
#include <iostream>

Projectile::Projectile(SDL_Renderer* rend, float posX, float posY, float sizeX, float sizeY, float speedX, float speedY, double angle, const char* tex)
{
	renderer = rend;
	this->posX = posX;
	this->posY = posY;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->speedX = speedX;
	this->speedY = speedY;
	this->angle = angle;
	std::cout << angle << '\n';
	sprite = TextureManager::LoadTexture(tex, renderer);
}

Projectile::~Projectile()
{
	if (sprite)
	{
		SDL_DestroyTexture(sprite);
		sprite = nullptr;
	}
}

void Projectile::Update()
{
	posX += speedX;
	posY += speedY;
}

void Projectile::Render(float dt)
{
	float posXAux = posX + speedX * dt;
	float posYAux = posY + speedY * dt;

	SDL_Rect projPos = { (int)(posXAux - sizeX / 2), (int)(posYAux - sizeY / 2),
		(int)(sizeX * .75f), (int)(sizeY * .75f) };
	SDL_Rect pos = { 0, 0, (int)sizeX, (int)sizeY };

	if (speedX > 0)
		SDL_RenderCopyEx(renderer, sprite, &pos, &projPos, angle, nullptr, SDL_FLIP_NONE);
	else if (speedX < 0)
		SDL_RenderCopyEx(renderer, sprite, &pos, &projPos, angle, nullptr, SDL_FLIP_HORIZONTAL);

}

GameObjID Projectile::GetID()
{
	return GameObjID();
}

float Projectile::GetPosX()
{
	return posX;
}

float Projectile::GetPosY()
{
	return posY;
}

float Projectile::GetSizeX()
{
	return sizeX;
}

float Projectile::GetSizeY()
{
	return sizeY;
}

bool Projectile::CheckCollision(GameObj* other)
{
	return false;
}
