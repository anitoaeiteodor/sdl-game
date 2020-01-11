#include "FireBow.h"

FireBow::FireBow(SDL_Renderer* rend, Vector2D pos, Vector2D size, const char* tex, float reloadSpeed)
	:RegularBow(rend, pos, size, tex, reloadSpeed)
{
	this->dmg = FIRE_BOW_DMG;
}

Arrow* FireBow::FireArrow(Vector2D dest)
{
	// create an explosion on impact
	return RegularBow::FireArrow(dest);
}

void FireBow::UpdateByPlayer(Vector2D pos, Orientation ori, double theta)
{
	RegularBow::UpdateByPlayer(pos, ori, theta);
}

GameObjID FireBow::GetID()
{
	return RegularBow::GetID();
}

void FireBow::Render(float dt)
{
	RegularBow::Render(dt);
}

void FireBow::Update()
{
}

Vector2D FireBow::GetPos()
{
	return pos;
}

Vector2D FireBow::GetSize()
{
	return size;
}

bool FireBow::CheckCollision(GameObj* other)
{
	return false;
}
