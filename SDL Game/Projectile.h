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
	~Projectile();

	void Update() override;
	void Render(float dt) override;
	GameObjID GetID() override;
	Vector2D GetPos() override;
	Vector2D GetSize() override;
	bool CheckCollision(GameObj* other) override;
};