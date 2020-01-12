#pragma once

#include "GameObj.h"
#include "Animation.h"
#include "Game.h"
#include "AnimationSystem.h"
#include "Bow.h"
#include "RegularBow.h"

#define PLAYER_DEATH_DELAY 2000

#define COLLISION_OFFSET_PLAYER_X -20
#define COLLISION_OFFSET_PLAYER_Y 10
#define COLLISION_SIZE_PLAYER_X 40
#define COLLISION_SIZE_PLAYER_Y 60


class Player : public GameObj {
	Vector2D speed;
	Vector2D mousePos;
	Vector2D collisionPos;
	Vector2D collisionSize;
	Bow* bow;
	double deathTime;

	AnimationSystem* anSys;
public:
	Player(SDL_Renderer* rend, Vector2D pos, Vector2D size);
	~Player();

	GameObjID GetID() override;
	void Update() override;
	void Render(float dt) override;
	Vector2D GetPos() override;
	Vector2D GetSize() override;

	void SetSpeed(Vector2D speed);
	void SetMousePos(Vector2D pos);
	void SetBow(Bow* bow);
	Arrow* FireArrow(Vector2D dest);
	void Die();
	bool IsAlive();
private:
	SDL_Texture* GetTex();
	void CreateAnimationSystem();
};