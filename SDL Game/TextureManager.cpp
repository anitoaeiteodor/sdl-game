#include "TextureManager.h"
#include <SDL_image.h>
#include <iostream>

SDL_Texture* TextureManager::LoadTexture(const char* fileName, SDL_Renderer* ren)
{
	SDL_Surface* surf = IMG_Load(fileName);
	if (!surf)
		Game::LogErr();

	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, surf);
	if (!tex)
		Game::LogErr();
	
	SDL_FreeSurface(surf);
	return tex;
}

SDL_Surface* TextureManager::CropSurface(SDL_Surface* spriteSheet, int x, int y, int width, int height)
{
	if (!spriteSheet)
		return nullptr;

	SDL_Surface* surface = SDL_CreateRGBSurface(spriteSheet->flags, width, height, 
		spriteSheet->format->BitsPerPixel, spriteSheet->format->Rmask,
		spriteSheet->format->Gmask, spriteSheet->format->Bmask, spriteSheet->format->Amask);

	SDL_Rect rect = { x, y, width, height };

	if (SDL_BlitSurface(spriteSheet, &rect, surface, nullptr))
		Game::LogErr();

	if (!surface)
		Game::LogErr();
	return surface;
}

SDL_Surface* TextureManager::LoadSurface(const char* fileName)
{
	SDL_Surface* surf = IMG_Load(fileName);
	if (!surf)
		Game::LogErr();
	return surf;
}

