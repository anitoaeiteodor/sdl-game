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

GameObjID RegularBow::GetID()
{
	return id;
}

void RegularBow::UpdateByPlayer(Vector2D pos, Orientation ori, double theta)
{
	this->pos = pos;
	this->ori = ori;
	this->renderTheta = theta;
}

void RegularBow::Render(float)
{
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	double theta = 0;

	Vector2D screenSize = { size.x * .5f, size.y * .5f };
	//if (playerState == State::Walk)
	//	theta = Bow::bowOffsetAngleWalk[anFrame];

	SDL_Rect screenPos = { (int)(pos.x - screenSize.x/2), (int)(pos.y - screenSize.y/2),
		(int)screenSize.x, (int)screenSize.y };
	SDL_Rect spriteRect = { 0, 0, (int)size.x, (int)size.y };

	if (ori == Orientation::Left)
	{
		flip = SDL_FLIP_HORIZONTAL;
	}

	SDL_RenderCopyEx(renderer, sprite, &spriteRect, &screenPos, renderTheta, nullptr, flip);
}

void RegularBow::Update()
{
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
