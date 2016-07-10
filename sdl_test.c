/*
 * A simple test of SDL.
 */
#include <stdio.h>
#include <SDL2/SDL.h>

int main(void)
{
	SDL_Window *win;
	SDL_Event event;
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

	// Wait for Enter to be pressed
	do {
		if(!SDL_WaitEvent(&event)) {
			fprintf(stderr, "Error waiting for an event: %s\n", SDL_GetError());
			return -1;
		}

		printf("Received an event: 0x%x\n", event.type);

		if(event.type == SDL_QUIT) {
			printf("Quitting.\n");
			break;
		}

		if(event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
			printf("Enter pressed.  Exiting.\n");
			break;
		}
	} while(1);

	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}
