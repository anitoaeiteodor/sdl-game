#include "Projectile.h"
#include "TextureManager.h"

Projectile::Projectile(SDL_Renderer* rend, float posX, float posY, float sizeX, float sizeY, float speedX, float speedY, const char* tex)
{
	renderer = rend;
	this->posX = posX;
	this->posY = posY;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->speedX = speedX;
	this->speedY = speedY;
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
	SDL_Rect projPos = { posX - sizeX / 2, posY - sizeY / 2, sizeX, sizeY };
	SDL_Rect pos = { 0, 0, sizeX, sizeY };

	if (speedX > 0)
		SDL_RenderCopyEx(renderer, sprite, &pos, &projPos, 0, nullptr, SDL_FLIP_NONE);
	else if (speedX < 0)
		SDL_RenderCopyEx(renderer, sprite, &pos, &projPos, 0, nullptr, SDL_FLIP_HORIZONTAL);

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

bool Projectile::CheckCollision(GameObj* other)
{
	return false;
}
