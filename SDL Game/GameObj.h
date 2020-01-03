#pragma once
#include <SDL.h>

#include "GameObjID.h"

class GameObj {
protected:
	SDL_Renderer* renderer;
	GameObjID id;
	float posX, posY;
	float sizeX, sizeY;

public:
	virtual GameObjID GetID() = 0;
	virtual void Update() = 0;
	virtual void Render(float) = 0;
	virtual float GetPosX() = 0;
	virtual float GetPosY() = 0;
	virtual bool CheckCollision(GameObj* other) = 0;
};