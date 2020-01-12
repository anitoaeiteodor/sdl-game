#pragma once
#include "Game.h"
#include "Enemy.h"
#include "Handler.h"

#include <vector>

enum class EnemyTypes {
	Skeleton_0, Goblin_0, Slime_0
};

struct Wave {
	Vector2D pos;
	int totalEnemies;
	int enTypes;
	std::vector<EnemyTypes> types;
	std::vector<int> numbers;
	int delay;
};

class Spawner {
	Vector2D pos;
	SDL_Renderer* renderer;
	std::vector<Wave> waves;
	int currWaveIndex;
	int waveStart;

public:
	Spawner(SDL_Renderer* renderer);
	~Spawner();

	void AddWaves(const char* file);
	Enemy* Spawn();
};