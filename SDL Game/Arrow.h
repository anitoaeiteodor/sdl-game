#pragma once

#include "Projectile.h"

#define ARROW_COLLISION_SIZE_X 30
#define ARROW_COLLISION_SIZE_Y 30

class Arrow : public Projectile {
	double theta;
	int dmg;
	Vector2D collisionPos;
	Vector2D collisionSize;

public:
	Arrow(SDL_Renderer* rend, Vector2D size, Vector2D src, Vector2D dest, int dmg, const char* tex);
	virtual ~Arrow();

	void Update() override;
	void Render(float dt) override;
	GameObjID GetID() override;

	Vector2D GetPos();
	Vector2D GetSize();
	int GetDmg();

	static const char* arrowSpritePath;
	static Vector2D arrowSize;
};

