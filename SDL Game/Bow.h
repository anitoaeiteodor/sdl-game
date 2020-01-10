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
	double renderTheta;
	Orientation ori;
	Arrows arrowType;
	SDL_Texture* sprite;

public:
	virtual Arrow* FireArrow(Vector2D dest) = 0;
	virtual void UpdateByPlayer(Vector2D pos, Orientation ori, double theta) = 0;
	static Vector2D bowSize;
	static Vector2D bowOffsetWalk[4];
	static Vector2D bowOffsetIdle[4];
	static double bowOffsetAngleWalk[4];
};

