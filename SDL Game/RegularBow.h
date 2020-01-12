#pragma once

#include "Bow.h"

#define REGULAR_BOW_DMG 10
#define FIRE_BOW_DMG 5

class RegularBow : public Bow {
public:
	RegularBow(SDL_Renderer* rend, Vector2D pos, Vector2D size, 
		const char* tex ,float reloadSpeed);

	Arrow* FireArrow(Vector2D dest) override;
	void UpdateByPlayer(Vector2D pos, Orientation ori, double theta) override;
	GameObjID GetID();
	void Render(float);
	void Update();
	Vector2D GetPos();
	Vector2D GetSize();
};