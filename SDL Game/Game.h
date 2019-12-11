#pragma once
#include <SDL.h>

#include "Handler.h"
#include "TextureManager.h"

class Game {
public:
	static int WINDOW_WIDTH;
	static int WINDOW_HEIGHT;
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Handler* handler;
	bool running;

	void Update();
	void Render(float dt);
	void HandleEvents();

public:
	Game();
	~Game();

	static void LogErr();
	void Init(const char* title, Uint32 xPos, Uint32 yPos, Uint32 sWidth, Uint32 sHeight, bool fullscreen);
	void Destroy();
	void Run();

	bool isRunning();
};