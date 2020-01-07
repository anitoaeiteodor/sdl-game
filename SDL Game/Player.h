#pragma once

#include "GameObj.h"
#include "Animation.h"
#include "Game.h"
#include "AnimationSystem.h"

class Player : public GameObj {
	float speedX, speedY;
	int mousePosX, mousePosY;
	float bowPosX, bowPosY;

	AnimationSystem* anSys;
public:
	Player(SDL_Renderer* rend, float posX, float posY, float sizeX, float sizeY);
	~Player();

	GameObjID GetID() override;
	void Update() override;
	void Render(float dt) override;
	float GetPosX() override;
	float GetPosY() override;
	float GetSizeX() override;
	float GetSizeY() override;
	bool CheckCollision(GameObj* other) override;

	void SetSpeed(float speedX, float speedY);
	void SetMousePos(int x, int y);
	void FireProj(int x, int y);
private:
	SDL_Texture* GetTex();
	void CreateAnimationSystem();
};