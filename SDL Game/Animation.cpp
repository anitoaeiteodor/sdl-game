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
		TextureManager::FreeTexture(frame);
	frames.clear();
}

void Animation::CreateFrames(const char* path, int nFrames, int width, int height, float speed)
{
	//SDL_Texture* tex = TextureManager::LoadTexture(R"(assets\Sprites\Player\Sword\Defence0\idle1.png)", renderer);
	//frames.push_back(tex);
	//tex = TextureManager::LoadTexture(R"(assets\Sprites\Player\Sword\Defence0\idle2.png)", renderer);
	//frames.push_back(tex);
	//tex = TextureManager::LoadTexture(R"(assets\Sprites\Player\Sword\Defence0\idle3.png)", renderer);
	//frames.push_back(tex);
	//tex = TextureManager::LoadTexture(R"(assets\Sprites\Player\Sword\Defence0\idle4.png)", renderer);
	//frames.push_back(tex);

	SDL_Surface* spriteSheet = TextureManager::LoadSurface(path);
	if (!spriteSheet)
		Game::LogErr();

	for (int i = 0; i < nFrames; i++)
	{
		SDL_Surface* surf = TextureManager::CropSurface(spriteSheet, i * width, 0, width, height);
		SDL_Texture* frame = SDL_CreateTextureFromSurface(renderer, surf);

		frames.push_back(frame);
		SDL_FreeSurface(surf);
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
		if (currFrame == frames.size() - 1)
			currFrame = 0;
		frame = frames[currFrame];
		acc = 0;
	}
	return frame;
}
