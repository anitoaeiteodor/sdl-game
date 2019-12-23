#pragma once

#include "GameObj.h"
#include "Animation.h"
#include "Game.h"
#include "AnimationSystem.h"

class Player : public GameObj {
	int speedX, speedY;
	AnimationSystem* anSys;
public:
	Player(SDL_Renderer* rend, int posX, int posY, int sizeX, int sizeY);
	~Player();

	GameObjID GetID() override;
	void Update() override;
	void Render(float dt) override;
	void SetSpeed(int speedX, int speedY);
private:
	SDL_Texture* GetTex();
	void CreateAnimationSystem();
};