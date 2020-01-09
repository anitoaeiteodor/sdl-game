#pragma once
#include "GameObj.h"
#include "Arrow.h"
#include "TextureManager.h"

enum class Arrows {
	Regular, Fire, Ice
};

class Bow : public GameObj {
protected:
	float reloadSpeed;
	float latestFire;
	float dmg;
	Arrows arrowType;
	SDL_Texture* sprite;

public:
	virtual Arrow* FireArrow(Vector2D dest) = 0;
	virtual void UpdatePos(Vector2D pos) = 0;
};