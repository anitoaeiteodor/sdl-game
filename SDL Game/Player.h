#pragma once

#include "GameObj.h"
#include "Animation.h"
#include "Game.h"
#include "AnimationSystem.h"

class Player : public GameObj {
	Vector2D speed;
	Vector2D mousePos;

	AnimationSystem* anSys;
public:
	Player(SDL_Renderer* rend, Vector2D pos, Vector2D size);
	~Player();

	GameObjID GetID() override;
	void Update() override;
	void Render(float dt) override;
	Vector2D GetPos() override;
	Vector2D GetSize() override;
	bool CheckCollision(GameObj* other) override;

	void SetSpeed(Vector2D speed);
	void SetMousePos(Vector2D pos);
	void FireProj(Vector2D dest);
private:
	SDL_Texture* GetTex();
	void CreateAnimationSystem();
};