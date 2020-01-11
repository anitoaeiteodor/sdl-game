#include "Enemy.h"

Enemy::Enemy(SDL_Renderer* rend, Vector2D pos, Vector2D size, const char* tex)
{
	this->renderer = rend;
	this->pos = pos;
	this->size = size;
	this->id = GameObjID::Monster;
	this->damage = REGULAR_MOB_DMG;
	this->health = REGULAR_MOB_HEALTH;
	CreateAnimationSystem();
}

GameObjID Enemy::GetID()
{
	return id;
}

void Enemy::Update()
{
}

void Enemy::Render(float dt)
{
}

Vector2D Enemy::GetPos()
{
	return Vector2D();
}

Vector2D Enemy::GetSize()
{
	return Vector2D();
}

bool Enemy::CheckCollision(GameObj* other)
{
	return false;
}

void Enemy::CreateAnimationSystem()
{
	anSys = new AnimationSystem(2);
	Animation* walk = new Animation(renderer);
	Animation* death = new Animation(renderer);

}
