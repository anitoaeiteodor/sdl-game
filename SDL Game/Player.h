#pragma once

#include "GameObj.h"
#include "Animation.h"
#include "Game.h"
#include "AnimationSystem.h"
#include "Bow.h"
#include "RegularBow.h"

class Player : public GameObj {
	Vector2D speed;
	Vector2D mousePos;
	Bow* bow;

	AnimationSystem* anSys;
public:
	Player(SDL_Renderer* rend, Vector2D pos, Vector2D size);
	~Player();

	GameObjID GetID() override;
	void Update() override;
	void Render(float dt) override;
	Vector2D GetPos() override;
	Vector2D GetSize() override;
	bool CheckCollision(GameObj* other) override;

	void SetSpeed(Vector2D speed);
	void SetMousePos(Vector2D pos);
	void SetBow(Bow* bow);
	Arrow* FireArrow(Vector2D dest);
	void Die();
private:
	SDL_Texture* GetTex();
	void CreateAnimationSystem();
};