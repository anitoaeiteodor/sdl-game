#include "Animation.h"

#include <iostream>
#include "TextureManager.h"

Animation::Animation(SDL_Renderer* ren)
{
	renderer = ren;
	fps = 0;
	timeStart = SDL_GetTicks();
}

Animation::~Animation()
{
	for (auto& frame : frames)
	{
		SDL_DestroyTexture(frame);
		frame = 0;
	}
	frames.clear();
}

void Animation::CreateFrames(const char* path, int rows, int cols, int width, int height, int fps)
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

	this->fps = fps;
}

int Animation::GetCurrentFrame()
{
	int frameToDraw = ((SDL_GetTicks() - timeStart) * fps / 1000) % (int)frames.size();
	return frameToDraw;
}

SDL_Texture* Animation::GetNextFrame()
{
	int frameToDraw = ((SDL_GetTicks() - timeStart) * fps / 1000) % (int)frames.size();
	SDL_Texture* frame = frames[frameToDraw];
	return frame;
}
