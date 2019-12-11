#pragma once
#include <SDL.h>

#include "GameObjID.h"

class GameObj {
private:
	GameObjID id;

public:
	virtual GameObjID GetID() = 0;
	virtual void Update() = 0;
	virtual void Render(float) = 0;
};