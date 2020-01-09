#pragma once

#include "Projectile.h"

class Arrow : public Projectile {
	double theta;
	float dmg;

public:
	Arrow(SDL_Renderer* rend, Vector2D size, Vector2D src, Vector2D dest, float dmg, const char* tex);
	~Arrow();

	void Update() override;
	void Render(float dt) override;
	GameObjID GetID() override;

	static const char* arrowSpritePath;
	static Vector2D arrowSize;
};

