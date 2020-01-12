#pragma once

#include "GameObj.h"
#include "TextureManager.h"
#include "AnimationSystem.h"
 
#define SKELETON_DMG 10
#define SKELETON_HEALTH 10
#define SKELETON_SPEED 2

#define GOBLIN_DMG 5
#define GOBLIN_HEALTH 2
#define GOBLIN_SPEED 7

#define SLIME_DMG 10
#define SLIME_HEALTH 20
#define SLIME_SPEED 1

#define SPRITE_SIZE_SKELETON_X 160
#define SPRITE_SIZE_SKELETON_Y 160

#define SPRITE_SIZE_GOBLIN_X 160
#define SPRITE_SIZE_GOBLIN_Y 160

#define SPRITE_SIZE_SLIME_X 160
#define SPRITE_SIZE_SLIME_Y 160

#define COLLISION_OFFSET_SKELETON_X -20
#define COLLISION_OFFSET_SKELETON_Y 0
#define COLLISION_SIZE_SKELETON_X 50
#define COLLISION_SIZE_SKELETON_Y 80

#define COLLISION_OFFSET_GOBLIN_X -10
#define COLLISION_OFFSET_GOBLIN_Y 30
#define COLLISION_SIZE_GOBLIN_X 25
#define COLLISION_SIZE_GOBLIN_Y 50

#define COLLISION_OFFSET_SLIME_X -20
#define COLLISION_OFFSET_SLIME_Y 50
#define COLLISION_SIZE_SLIME_X 60
#define COLLISION_SIZE_SLIME_Y 30

#define SKELETON_DEATH_DELAY 1500
#define GOBLIN_DEATH_DELAY 1500
#define SLIME_DEATH_DELAY 3000

class Enemy : public GameObj {
protected:
	Vector2D speed;
	Vector2D playerPos;
	AnimationSystem* anSys;
	Vector2D collisionPos;
	Vector2D collisionSize;
	int health;
	int damage;
	double deathTime;

public:
	Enemy(SDL_Renderer* rend, Vector2D pos);
	virtual ~Enemy();

	GameObjID GetID() override;
	Vector2D GetPos();
	Vector2D GetSize();
	int GetDmg();

	void Update() override;
	void Render(float dt) override;
	void CreateAnimationSystem();

	void SetPlayerPos(Vector2D pos);
	void Die();
	bool IsAlive();
	int TakeDmg(int amount);
};