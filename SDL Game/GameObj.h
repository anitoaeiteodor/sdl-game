#pragma once
#include <SDL.h>

enum class State {
	Walk, Idle
};

enum class Orientation {
	Left, Right
};

enum class GameObjID
{
	Player, Monster, Arrow, Bow
};

struct Vector2D {
	float x, y;

	Vector2D operator+(const Vector2D& other)
	{
		Vector2D third;
		third.x = x + other.x;
		third.y = y + other.y;
		return third;
	}

	Vector2D operator*(float scalar)
	{
		Vector2D ret;
		ret.x = x * scalar;
		ret.y = y * scalar;
		return ret;
	}
};

class GameObj {
protected:
	SDL_Renderer* renderer;
	GameObjID id;
	Vector2D pos;
	Vector2D size;

public:
	virtual GameObjID GetID() = 0;
	virtual void Update() = 0;
	virtual void Render(float) = 0;
	virtual Vector2D GetPos() = 0;
	virtual Vector2D GetSize() = 0;
	virtual bool CheckCollision(GameObj* other) = 0;
};