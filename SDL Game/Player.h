#pragma once

#include "GameObj.h"
#include "Animation.h"
#include "Game.h"
#include "AnimationSystem.h"

class Player : public GameObj {
	float speedX, speedY;
	AnimationSystem* anSys;
public:
	Player(SDL_Renderer* rend, float posX, float posY, float sizeX, float sizeY);
	~Player();

	GameObjID GetID() override;
	void Update() override;
	void Render(float dt) override;
	float GetPosX() override;
	float GetPosY() override;
	bool CheckCollision(GameObj* other) override;

	void SetSpeed(float speedX, float speedY);
private:
	SDL_Texture* GetTex();
	void CreateAnimationSystem();
};