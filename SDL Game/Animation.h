#pragma once

#include <SDL_image.h>
#include <vector>

class Animation {
private:
	int nFrames;
	int currFrame;
	std::vector<SDL_Texture*> frames;
public:
	Animation();
	~Animation();
	SDL_Texture* NextFrame();
	void CreateAnimation();
};