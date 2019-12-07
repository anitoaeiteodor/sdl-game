#pragma once
#include <SDL.h>
#include <vector>


class Animation {
private:
	SDL_Renderer* renderer;
	std::vector<SDL_Texture*> frames;
	int currFrame;
	float speed;
	float acc;

public:
	Animation(SDL_Renderer* ren);
	~Animation();
	void CreateFrames(const char* path, int rows, int cols, int width, int height, float speed);
	SDL_Texture* GetNextFrame(float dt);
};