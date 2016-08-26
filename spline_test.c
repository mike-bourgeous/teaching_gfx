/*
 * Learning to draw Bézier curves in the most brute-force way.
 */
#include <stdio.h>
#include <inttypes.h>
#include <math.h>
#include <SDL2/SDL.h>

// A 2D point
struct point {
	float x;
	float y;
};

// An RGB color with values from 0-255
struct color {
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

// function to draw curve
// function to caculate point on curve
//   control points
//   color

// Returns a value linearly interpolated between v1 and v2 by t.  t==0 returns
// v1, t==1 returns v2.
float interp(float v1, float v2, float t)
{
	return (1 - t) * v1 + t * v2;
}

// Returns a 2D point linearly interpolated between p1 and p2 by t.
struct point interp_point(struct point p1, struct point p2, float t)
{
	return (struct point){
		.x = interp(p1.x, p2.x, t),
		.y = interp(p1.y, p2.y, t),
	};
}

// Returns a point on the linear spline with control points c0 and c1 at t from
// 0 to 1.
struct point linear_spline(struct point c0, struct point c1, float t)
{
	return interp_point(c0, c1, t);
}

// Returns a pseudorandom point within the range ( [0, w), [0, h) ).
struct point random_point(int w, int h)
{
	return (struct point){
		.x = rand() % w,
		.y = rand() % h
	};
}

// Sets a single pixel on the given surface to the given color.
void set_pixel(SDL_Surface *dest, int x, int y, struct color clr)
{
	uint32_t color = SDL_MapRGB(dest->format, clr.r, clr.g, clr.b);
	if(SDL_FillRect(dest, &(SDL_Rect){x: x, y: y, w: 1, h: 1}, color)) {
		fprintf(stderr, "Error drawing a pixel: %s\n", SDL_GetError());
		abort();
	}
}

// Draws a linear spline with control points c0 and c1 on the given surface.
void draw_linear_spline(SDL_Surface *dest, struct point c0, struct point c1, struct color clr)
{
	struct point p;
	float t;

	for(t = 0; t <= 1; t += 0.001) {
		p = linear_spline(c0, c1, t);
		set_pixel(dest, p.x, p.y, clr);
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
	int run = 1;
	do {
		struct color clr = {
			.r = rand() % 255,
			.g = rand() % 255,
			.b = rand() % 255
		};

		draw_linear_spline(
				screen,
				random_point(screen->w, screen->h),
				random_point(screen->w, screen->h),
				clr
				);
		SDL_UpdateWindowSurface(win);

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
