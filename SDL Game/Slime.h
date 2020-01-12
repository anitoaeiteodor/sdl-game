#pragma once

#include "Enemy.h"

class Slime : public Enemy {
public:
	Slime(SDL_Renderer* rend, Vector2D pos);
	virtual ~Slime();

	void Update() override;
	void Render(float dt) override;
	void CreateAnimationSystem();
};