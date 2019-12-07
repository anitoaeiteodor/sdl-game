#include "Animation.h"

#include <iostream>
#include "TextureManager.h"

Animation::Animation(SDL_Renderer* ren)
{
	renderer = ren;
	currFrame = 0;
	acc = 0;
	speed = 0;
}

Animation::~Animation()
{
	for (auto& frame : frames)
		SDL_DestroyTexture(frame);
	frames.clear();
}

void Animation::CreateFrames(const char* path, int rows, int cols, int width, int height, float speed)
{
	SDL_Surface* spriteSheet = TextureManager::LoadSurface(path);
	if (!spriteSheet)
		Game::LogErr();

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			SDL_Surface* surf = TextureManager::CropSurface(spriteSheet, i * width, j * height, width, height);
			SDL_Texture* frame = SDL_CreateTextureFromSurface(renderer, surf);

			frames.push_back(frame);
			SDL_FreeSurface(surf);
		}
	}

	this->speed = speed;
}

SDL_Texture* Animation::GetNextFrame(float dt)
{
	SDL_Texture* frame = frames[currFrame];
	acc += dt;
	if (acc >= speed)
	{
		currFrame++;
		if (currFrame == frames.size())
			currFrame = 0;
		frame = frames[currFrame];
		acc = 0;
	}
	return frame;
}
