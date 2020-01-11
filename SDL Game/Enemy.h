#pragma once

#include "GameObj.h"
#include "TextureManager.h"
#include "AnimationSystem.h"

#define REGULAR_MOB_DMG 5
#define REGULAR_MOB_HEALTH 10

class Enemy : public GameObj {
	Vector2D speed;
	AnimationSystem* anSys;
	int health;
	int damage;

public:
	Enemy(SDL_Renderer* rend, Vector2D pos, Vector2D size,
		const char* tex);
	GameObjID GetID() override;
	void Update() override;
	void Render(float dt) override;
	Vector2D GetPos();
	Vector2D GetSize();
	bool CheckCollision(GameObj* other);
	void CreateAnimationSystem();
};