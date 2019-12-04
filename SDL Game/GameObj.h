#pragma once
#include <SDL.h>

#include "GameObjID.h"

class GameObj {
private:
	GameObjID id;

public:
	GameObjID GetID();
	virtual void Update();
	virtual void Render(float);
};