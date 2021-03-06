#pragma once

#include "RegularBow.h"

class FireBow : public RegularBow {
public:
	FireBow(SDL_Renderer* rend, Vector2D pos, Vector2D size,
		const char* tex, float reloadSpeed);

	Arrow* FireArrow(Vector2D dest) override;
	void UpdateByPlayer(Vector2D pos, Orientation ori, double theta) override;
	GameObjID GetID();
	void Render(float dt);
	void Update();
	Vector2D GetPos();
	Vector2D GetSize();
	bool CheckCollision(GameObj* other);
};