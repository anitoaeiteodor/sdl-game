#include "RegularBow.h"

RegularBow::RegularBow(SDL_Renderer* rend, Vector2D pos, Vector2D size, const char* tex, float reloadSpeed)
{
	renderer = rend;
	this->pos = pos;
	this->size = size;
	this->arrowType = Arrows::Regular;
	this->dmg = REGULAR_BOW_DMG;
	this->id = GameObjID::Bow;
	this->reloadSpeed = reloadSpeed;
	sprite = TextureManager::LoadTexture(tex, renderer);
}

Arrow* RegularBow::FireArrow(Vector2D dest)
{
	Arrow* arrow = nullptr;

	if (latestFire == 0 || (SDL_GetTicks() / 1000.0f - latestFire > reloadSpeed))
	{
		latestFire = SDL_GetTicks() / 1000.0f;
		arrow = new Arrow(renderer, Arrow::arrowSize, pos, dest, dmg, Arrow::arrowSpritePath);
	}
	else
		arrow = nullptr;

	return arrow;
}

void RegularBow::UpdatePos(Vector2D pos)
{
	this->pos = pos;
}

GameObjID RegularBow::GetID()
{
	return id;
}

void RegularBow::Update()
{
	// This object is tied to the player and the player entity is responsible for 
	// updating its position, nothing to do here
}

void RegularBow::Render(float)
{
	// to do...
}

Vector2D RegularBow::GetPos()
{
	return pos;
}

Vector2D RegularBow::GetSize()
{
	return size;
}

bool RegularBow::CheckCollision(GameObj* other)
{
	return false;
}
