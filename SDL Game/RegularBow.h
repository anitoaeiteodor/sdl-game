#pragma once

#include "Bow.h"

#define REGULAR_BOW_DMG 10

class RegularBow : public Bow {
public:
	RegularBow(SDL_Renderer* rend, Vector2D pos, Vector2D size, 
		const char* tex,float reloadSpeed);

	Arrow* FireArrow(Vector2D dest) override;
	void UpdatePos(Vector2D pos) override;
	GameObjID GetID();
	void Update();
	void Render(float);
	Vector2D GetPos();
	Vector2D GetSize();
	bool CheckCollision(GameObj* other);
};