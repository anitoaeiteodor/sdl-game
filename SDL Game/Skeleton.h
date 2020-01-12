#pragma once

#include "Enemy.h"

class Skeleton : public Enemy {
public:
	Skeleton(SDL_Renderer* rend, Vector2D pos);
	virtual ~Skeleton();

	void Update() override;
	void Render(float dt) override;
	void CreateAnimationSystem();
};