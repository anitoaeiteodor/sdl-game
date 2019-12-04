#include "TextureManager.h"
#include <SDL_image.h>
#include <iostream>

SDL_Texture* TextureManager::LoadTexture(const char* fileName, SDL_Renderer* ren)
{
	SDL_Surface* surf = IMG_Load(fileName);
	if (!surf)
		Game::LogErr();

	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, surf);
	if (!surf)
		Game::LogErr();
	
	SDL_FreeSurface(surf);
	return tex;
}

void TextureManager::FreeTexture(SDL_Texture* tex)
{
	if (!tex)
		return;
	SDL_DestroyTexture(tex);
}
