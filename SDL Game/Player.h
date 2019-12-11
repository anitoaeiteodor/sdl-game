#pragma once

#include "GameObj.h"
#include "Animation.h"
#include "Game.h"

class Player : public GameObj {
	int speedX, speedY;
	SDL_Texture* tex;
public:
	Player(SDL_Renderer* rend, int posX, int posY, int sizeX, int sizeY);
	~Player();

	GameObjID GetID() override;
	void Update() override;
	void Render(float dt) override;
	void SetSpeed(int speedX, int speedY);
};