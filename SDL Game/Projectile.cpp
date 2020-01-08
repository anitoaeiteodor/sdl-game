#include "Projectile.h"
#include "TextureManager.h"
#include <iostream>

Projectile::Projectile(SDL_Renderer* rend, Vector2D size, Vector2D src, Vector2D dest, const char* tex)
{
	renderer = rend;
	this->pos = src;
	this->size = size;
	double theta = atan(((float)dest.y - src.y) / ((float)dest.x - src.x));
	if (dest.x < src.x)
		theta += M_PI;
	this->speed = {(float)(10 * cos(theta)), (float)(10 * sin(theta))};
	this->src = src;
	this->dest = dest;
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
	pos = pos + speed;
}

void Projectile::Render(float dt)
{
	Vector2D posAux = pos + speed * dt;

	SDL_Rect projPos = { (int)(posAux.x - size.x / 2), (int)(posAux.y - size.y / 2),
		(int)(size.x * .75f), (int)(size.y * .75f) };
	SDL_Rect pos = { 0, 0, (int)size.x, (int)size.y };

	if (speed.x > 0)
		SDL_RenderCopyEx(renderer, sprite, &pos, &projPos, 0, nullptr, SDL_FLIP_NONE);
	else if (speed.x < 0)
		SDL_RenderCopyEx(renderer, sprite, &pos, &projPos, 0, nullptr, SDL_FLIP_HORIZONTAL);

}

GameObjID Projectile::GetID()
{
	return GameObjID();
}

Vector2D Projectile::GetPos()
{
	return pos;
}

Vector2D Projectile::GetSize()
{
	return size;
}


bool Projectile::CheckCollision(GameObj* other)
{
	return false;
}
