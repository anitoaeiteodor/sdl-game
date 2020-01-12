#pragma once

#include "Enemy.h"

class Goblin : public Enemy {
public:
	Goblin(SDL_Renderer* rend, Vector2D pos);
	virtual ~Goblin();

	void Update() override;
	void Render(float dt) override;
	void CreateAnimationSystem();
};