#include "Enemy.h"
#include <stdlib.h>
#include <time.h>

Enemy::Enemy(SDL_Renderer* rend, Vector2D pos)
{
	this->renderer = rend;
	this->pos = pos;
	this->id = GameObjID::Monster;
	this->deathTime = 0;

	anSys = nullptr;
	collisionPos = { 0, 0 };
	collisionSize = { 0, 0 };
	speed = { 0, 0 };
	damage = 0;
	health = 0;
	playerPos = { 0, 0 };
}

Enemy::~Enemy()
{
	if (anSys)
	{
		delete anSys;
		anSys = nullptr;
	}
}

GameObjID Enemy::GetID()
{
	return id;
}

void Enemy::Update()
{
	if (deathTime)
		return;

	anSys->ProcessInput(Command::RUN);

	pos = pos + speed;
}

void Enemy::Render(float dt)
{
	Vector2D posAux = pos + speed * dt;

	SDL_Rect enemyPos = { (int)(posAux.x - size.x / 2), (int)(posAux.y - size.y / 2),
		(int)size.x, (int)size.y };
	SDL_Rect spritePos = { 0, 0, (int)size.x, (int)size.y };
	
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (!deathTime)
	{
		if (playerPos.x < pos.x)
			flip = SDL_FLIP_HORIZONTAL;
	}

	SDL_RenderCopyEx(renderer, anSys->GetNextFrame(), &spritePos, &enemyPos, 0, nullptr, flip);

}

Vector2D Enemy::GetPos()
{
	if (deathTime)
		return { 0, 0 };
	return pos + collisionPos;
}

Vector2D Enemy::GetSize()
{
	if (deathTime)
		return { 0, 0 };
	return collisionSize;
}

int Enemy::GetDmg()
{
	return damage;
}

void Enemy::CreateAnimationSystem()
{

}

void Enemy::SetPlayerPos(Vector2D pos)
{
	playerPos = pos;
}

void Enemy::Die()
{
	speed = { 0, 0 };
	deathTime = SDL_GetTicks();
	anSys->ProcessInput(Command::DEATH);
}

bool Enemy::IsAlive()
{
	if (!deathTime)
		return true;
	return (SDL_GetTicks() - deathTime < SKELETON_DEATH_DELAY);
}

int Enemy::TakeDmg(int amount)
{
	health -= amount;
	return health;
}
