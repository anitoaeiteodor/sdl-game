#pragma once

#include "GameObj.h"

class Projectile : public GameObj {
	float speedX, speedY;
	SDL_Texture* sprite;

public:
	Projectile(SDL_Renderer* rend, float posX, float posY, float sizeX, float sizeY, float speedX, float speedY, const char* tex);
	~Projectile();

	void Update() override;
	void Render(float dt) override;
	GameObjID GetID() override;
	float GetPosX() override;
	float GetPosY() override;
	bool CheckCollision(GameObj* other) override;
};