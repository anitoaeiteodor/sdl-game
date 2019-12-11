#pragma once
#include <SDL.h>

#include "GameObjID.h"

class GameObj {
protected:
	SDL_Renderer* renderer;
	GameObjID id;
	int posX, posY;
	int sizeX, sizeY;

public:
	virtual GameObjID GetID() = 0;
	virtual void Update() = 0;
	virtual void Render(float) = 0;
};