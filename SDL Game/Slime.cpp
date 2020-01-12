#include "Slime.h"

Slime::Slime(SDL_Renderer* rend, Vector2D pos)
	: Enemy(rend, pos)
{
	this->damage = SLIME_DMG;
	this->health = SLIME_HEALTH;
	this->size = { SPRITE_SIZE_SLIME_X, SPRITE_SIZE_SLIME_Y };
	collisionPos = { COLLISION_OFFSET_SLIME_X, COLLISION_OFFSET_SLIME_Y };
	collisionSize = { COLLISION_SIZE_SLIME_X, COLLISION_SIZE_SLIME_Y };
	CreateAnimationSystem();
}

Slime::~Slime()
{
	if (anSys)
	{
		delete anSys;
		anSys = nullptr;
	}
}

void Slime::Update()
{
	double theta = atan(((float)playerPos.y - pos.y) / ((float)playerPos.x - pos.x));
	if (playerPos.x < pos.x)
		theta += M_PI;

	speed = { (float)(SLIME_SPEED * cos(theta)), (float)(SLIME_SPEED * sin(theta)) };

	Enemy::Update();
}

void Slime::Render(float dt)
{
	Enemy::Render(dt);
}

void Slime::CreateAnimationSystem()
{
	anSys = new AnimationSystem(2);
	Animation* walk = new Animation(renderer);
	Animation* death = new Animation(renderer);

	walk->CreateFrames(R"(assets\Sprites\Monsters\slime_one_walk.png)", 2, 2, 160, 160, 12, true);
	death->CreateFrames(R"(assets\Sprites\Monsters\slime_one_death.png)", 2, 2, 160, 160, 3, false);

	anSys->AddAnimation(walk);
	anSys->AddAnimation(death);

	anSys->AddTrigger(0, 0, Command::RUN);
	anSys->AddTrigger(0, 1, Command::DEATH);
	anSys->AddTrigger(1, 1, Command::IDLE);
}
