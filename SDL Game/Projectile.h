#pragma once

#include "GameObj.h"

class Projectile : public GameObj {
protected:
	Vector2D speed;
	Vector2D src;
	Vector2D dest;
	SDL_Texture* sprite;

public:
	Projectile(SDL_Renderer* rend, Vector2D size, Vector2D src, Vector2D dest, const char* tex);
	virtual ~Projectile();

	virtual void Update() override;
	virtual void Render(float dt) override;
	virtual GameObjID GetID() override;
	virtual Vector2D GetPos() override;
	virtual Vector2D GetSize() override;
};