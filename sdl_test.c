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

// Draws funky sinusoidal color patterns on the given surface.
void draw_colors(SDL_Surface *dest, float r_omega, float r_phi, float g_omega, float g_phi, float b_omega, float b_phi)
{
	for(int i = 0; i < dest->w * dest->h; i++) {
		uint8_t r = sinf(i * r_omega + r_phi) * 127 + 127;
		uint8_t g = sinf(i * g_omega + g_phi) * 127 + 127;
		uint8_t b = sinf(i * b_omega + b_phi) * 127 + 127;
		set_pixel(dest, i % dest->w, i / dest->w, r, g, b);
	}
}

int main(void)
{
	SDL_Window *win;
	SDL_Surface *screen;
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

	// Make it funky
	float phi = 0.0f;
	int run = 1;
	do {
		float f = sin(100.0 * phi);

		draw_colors(screen,
				M_PI / (128.0f + 0.25 * f), 110 * phi + 0.1 * f,
				M_PI / (93000.0 - 1120 * f), phi * 170,
				M_PI / (120000.0 + 55190 * f), phi * -80);
		SDL_UpdateWindowSurface(win);

		phi += 0.001f;

		while(SDL_PollEvent(&event)) {
			printf("Received an event: 0x%x\n", event.type);

			if(event.type == SDL_QUIT) {
				printf("Quitting.\n");
				run = 0;
				break;
			}

			if(event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
				printf("Enter pressed.  Exiting.\n");
				run = 0;
				break;
			}
		}
	} while(run);

	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}
