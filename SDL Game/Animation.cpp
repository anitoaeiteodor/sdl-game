#include "Animation.h"

#include <iostream>
#include "TextureManager.h"

Animation::Animation(SDL_Renderer* ren)
{
	renderer = ren;
	fps = 0;
	timeStart = SDL_GetTicks();
	loop = false;
}

Animation::~Animation()
{
	for (auto& frame : frames)
	{
		if(frame)
			SDL_DestroyTexture(frame);
		frame = nullptr;
	}
	frames.clear();
}

void Animation::CreateFrames(const char* path, int rows, int cols, int width, int height, int fps, bool loop)
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
	this->loop = loop;
	this->fps = fps;
}

int Animation::GetCurrentFrame()
{
	int frameToDraw = ((SDL_GetTicks() - timeStart) * fps / 1000) % (int)frames.size();
	return frameToDraw;
}

SDL_Texture* Animation::GetNextFrame()
{
	static SDL_Texture* lastFrame = nullptr;
	if (lastFrame)
		return lastFrame;

	int frameToDraw = ((SDL_GetTicks() - timeStart) * fps / 1000) % (int)frames.size();
	if (!loop && frameToDraw == frames.size() - 1)
	{
		lastFrame = frames[frameToDraw];
		return lastFrame;
	}
	SDL_Texture* frame = frames[frameToDraw];
	return frame;
}
