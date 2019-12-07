#pragma once

#include "Game.h"

class TextureManager {
public:
	static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren);
	static SDL_Surface* LoadSurface(const char* fileName);
	static SDL_Surface* CropSurface(SDL_Surface* spriteSheet, int x, int y, int width, int height);
	
	static void FreeTexture(SDL_Texture* tex);
	static void FreeSurface(SDL_Surface* surf);
};