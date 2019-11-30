#include <SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	bool flag = 1;

	while (1)
	{
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

		SDL_RenderClear(renderer);

		SDL_Event event;

		if (flag)
			std::cout << "Flag is on\n";

		while (!SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
			{
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
				exit(0);
			}
			case SDL_MOUSEBUTTONDOWN:
				flag = 0;
			default:
				break;
			}
		}

		SDL_Rect rect = { 100, 100, 200, 200 };
		SDL_SetRenderDrawColor(renderer, 13, 92, 125, 220);
		SDL_RenderFillRect(renderer, &rect);

		SDL_RenderPresent(renderer);

	}

	return 0;
}