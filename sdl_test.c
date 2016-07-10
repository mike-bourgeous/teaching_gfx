/*
 * A simple test of SDL.
 */
#include <SDL2/SDL.h>

int main(void)
{
	SDL_Window *win;
	int ret;

	ret = SDL_Init(SDL_INIT_EVERYTHING);
	if(ret) {
		fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
		return -1;
	}

	win = SDL_CreateWindow("Testing SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, 0);
	if(win == NULL) {
		fprintf(stderr, "Error creating SDL window: %s\n", SDL_GetError());
		return -1;
	}

	// TODO: do stuff here

	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}
