/*
 * A simple test of SDL.
 */
#include <stdio.h>
#include <inttypes.h>
#include <math.h>
#include <SDL2/SDL.h>

// Sets a single pixel on the given surface.
void set_pixel(SDL_Surface *dest, int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
	uint32_t color = SDL_MapRGB(dest->format, r, g, b);
	if(SDL_FillRect(dest, &(SDL_Rect){x: x, y: y, w: 1, h: 1}, color)) {
		fprintf(stderr, "Error drawing a pixel: %s\n", SDL_GetError());
		abort();
	}
}

int main(void)
{
	SDL_Window *win;
	SDL_Surface *screen;
	SDL_Event event;
	int ret;
	int i;

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

	screen = SDL_GetWindowSurface(win);
	if(screen == NULL) {
		fprintf(stderr, "Error getting window drawing surface: %s\n", SDL_GetError());
		return -1;
	}

	printf("Screen pixel format: 0x%x (%d bits per pixel)\n", screen->format->format, screen->format->BitsPerPixel);

	// Clear the screen
	if(SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0))) {
		fprintf(stderr, "Error clearing the screen: %s\n", SDL_GetError());
		return -1;
	}
	if(SDL_UpdateWindowSurface(win)) {
		fprintf(stderr, "Error updating window surface after clearing: %s\n", SDL_GetError());
		return -1;
	}

	// Write some pixels
	for(i = 0; i < screen->w * screen->h; i++) {
		uint8_t r = sin(i * M_PI / 128.0) * 127 + 127;
		uint8_t g = sin(i * M_PI / 93000.0) * 127 + 127;
		uint8_t b = sin(i * M_PI / 120000.0) * 127 + 127;
		set_pixel(screen, i % screen->w, i / screen->w, r, g, b);
	}
	SDL_UpdateWindowSurface(win);
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
