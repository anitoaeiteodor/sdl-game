#include "Spawner.h"
#include "Skeleton.h"
#include "Goblin.h"
#include "Slime.h"

#include <iostream>
#include <fstream>

Spawner::Spawner(SDL_Renderer* renderer)
{
	pos = { 0, 0 };
	this->renderer = renderer;
	waveStart = 0;
	currWaveIndex = 0;
}

Spawner::~Spawner()
{

}

void Spawner::AddWaves(const char* file)
{
	int nWaves;
	std::ifstream fin(file);

	fin >> pos.x >> pos.y;
	fin >> nWaves;
	while (nWaves--)
	{
		Wave newWave;
		fin >> newWave.totalEnemies;
		fin >> newWave.enTypes;
		for (int i = 0; i < newWave.enTypes; i++)
		{
			int e;
			fin >> e;
			newWave.types.push_back((EnemyTypes)e);
		}
		for (int i = 0; i < newWave.enTypes; i++)
		{
			int number;
			fin >> number;
			newWave.numbers.push_back(number);
		}
		fin >> newWave.delay;
		
		waves.push_back(newWave);
	}
}

Enemy* Spawner::Spawn()
{
	Enemy* enemy = nullptr;
	if (currWaveIndex >= waves.size())
		return enemy;

	if (waves[currWaveIndex].totalEnemies == 0)
	{
		std::cout << "Started new wave\n";
		currWaveIndex++;
		waveStart = SDL_GetTicks();
		return nullptr;
	}
	else
	{
		for (size_t i = 0; i < waves[currWaveIndex].types.size(); i++)
		{
			if (waves[currWaveIndex].numbers[i] && ((int)SDL_GetTicks() - waveStart > waves[currWaveIndex].delay))
			{
				switch (waves[currWaveIndex].types[i])
				{
				case EnemyTypes::Skeleton_0:
					enemy = new Skeleton(renderer, pos);
					break;
				case EnemyTypes::Goblin_0:
					enemy = new Goblin(renderer, pos);
					break;
				case EnemyTypes::Slime_0:
					enemy = new Slime(renderer, pos);
					break;
				default:
					break;
				}

				waves[currWaveIndex].numbers[i]--;
				waves[currWaveIndex].totalEnemies--;
				waveStart = SDL_GetTicks();
				break;
			}
		}
	}
	return enemy;
}
