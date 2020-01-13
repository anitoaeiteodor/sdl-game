#include "Goblin.h"

Goblin::Goblin(SDL_Renderer* rend, Vector2D pos)
	: Enemy(rend, pos)
{
	this->damage = GOBLIN_DMG;
	this->health = GOBLIN_HEALTH;
	this->size = { SPRITE_SIZE_GOBLIN_X, SPRITE_SIZE_GOBLIN_Y };
	collisionPos = { COLLISION_OFFSET_GOBLIN_X, COLLISION_OFFSET_GOBLIN_Y };
	collisionSize = { COLLISION_SIZE_GOBLIN_X, COLLISION_SIZE_GOBLIN_Y };
	CreateAnimationSystem();
}

Goblin::~Goblin()
{
	if (anSys)
	{
		delete anSys;
		anSys = nullptr;
	}
}

void Goblin::Update()
{
	if (!playerPos.x == 0)
	{
		double theta = atan(((float)playerPos.y - pos.y) / ((float)playerPos.x - pos.x));
		if (playerPos.x < pos.x)
			theta += M_PI;

		speed = { (float)(GOBLIN_SPEED * cos(theta)), (float)(GOBLIN_SPEED * sin(theta)) };
	}
	else if (speed.x == 0 && speed.y == 0)
		speed = { GOBLIN_SPEED, GOBLIN_SPEED };
	Enemy::Update();
}

void Goblin::Render(float dt)
{
	Enemy::Render(dt);
}

void Goblin::CreateAnimationSystem()
{
	anSys = new AnimationSystem(2);
	Animation* walk = new Animation(renderer);
	Animation* death = new Animation(renderer);

	walk->CreateFrames(R"(assets\Sprites\Monsters\goblin_one_walk.png)", 2, 2, 160, 160, 12, true);
	death->CreateFrames(R"(assets\Sprites\Monsters\goblin_one_death.png)", 2, 2, 160, 160, 4, false);

	anSys->AddAnimation(walk);
	anSys->AddAnimation(death);

	anSys->AddTrigger(0, 0, Command::RUN);
	anSys->AddTrigger(0, 1, Command::DEATH);
	anSys->AddTrigger(1, 1, Command::IDLE);
}
