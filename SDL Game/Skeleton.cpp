#include "Skeleton.h"

Skeleton::Skeleton(SDL_Renderer* rend, Vector2D pos)
	: Enemy(rend, pos)
{
	this->damage = SKELETON_DMG;
	this->health = SKELETON_HEALTH;
	this->size = { SPRITE_SIZE_SKELETON_X, SPRITE_SIZE_SKELETON_Y };
	collisionPos = { COLLISION_OFFSET_SKELETON_X, COLLISION_OFFSET_SKELETON_Y };
	collisionSize = { COLLISION_SIZE_SKELETON_X, COLLISION_SIZE_SKELETON_Y };
	CreateAnimationSystem();
}

Skeleton::~Skeleton()
{
	if (anSys)
	{
		delete anSys;
		anSys = nullptr;
	}
}

void Skeleton::Update()
{
	double theta = atan(((float)playerPos.y - pos.y) / ((float)playerPos.x - pos.x));
	if (playerPos.x < pos.x)
		theta += M_PI;

	speed = { (float)(SKELETON_SPEED * cos(theta)), (float)(SKELETON_SPEED * sin(theta)) };
	
	Enemy::Update();
}

void Skeleton::Render(float dt)
{
	Enemy::Render(dt);
}

void Skeleton::CreateAnimationSystem()
{
	anSys = new AnimationSystem(2);
	Animation* walk = new Animation(renderer);
	Animation* death = new Animation(renderer);

	walk->CreateFrames(R"(assets\Sprites\Monsters\skeleton_one_walk.png)", 2, 2, 160, 160, 12, true);
	death->CreateFrames(R"(assets\Sprites\Monsters\skeleton_one_death.png)", 2, 2, 160, 160, 4, false);
	
	anSys->AddAnimation(walk);
	anSys->AddAnimation(death);

	anSys->AddTrigger(0, 0, Command::RUN);
	anSys->AddTrigger(0, 1, Command::DEATH);
	anSys->AddTrigger(1, 1, Command::IDLE);
}
