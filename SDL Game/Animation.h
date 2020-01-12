#pragma once
#include <SDL.h>
#include <vector>


class Animation {
private:
	SDL_Renderer* renderer;
	std::vector<SDL_Texture*> frames;
	int fps;
	int timeStart;
	bool loop;
	SDL_Texture* lastFrame;
public:
	Animation(SDL_Renderer* ren);
	~Animation();

	void CreateFrames(const char* path, int rows, int cols, int width, int height, int fps, bool loop);
	int GetCurrentFrame();
	SDL_Texture* GetNextFrame();
	void ResetAnimation();
};