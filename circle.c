/*
 * Uses teaching gfx primitives to draw a circle.
 * Mar. 7, 2016
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "gfx.h"

// Draws a circle on the given image with the given image dimensions.
void circle(uint8_t *img, int w, int h)
{
	float r = w < h ? w * 0.5f : h * 0.5f;
	float xc = 0.5f * w;
	float yc = 0.5f * h;
	float t;

	for(t = 0; t <= 2.0f * M_PI; t += 0.0001 * M_PI) {
		int x = r * cosf(t) + xc;
		int y = r * sinf(t) + yc;

		fprintf(stderr, "t=%.3f x=%d y=%d\n", t, x, y);

		setpx(img, w, x, y, rand() % 127 + 128);
	}
}

int main(int argc, char *argv[])
{
	struct timespec now;
	uint8_t *img;
	int w, h;
	int sz;

	if(argc != 3) {
		fprintf(stderr, "Usage: %s width height\n", argv[0]);
		return 1;
	}

	// Seed the random number generator to get different results each time
	clock_gettime(CLOCK_MONOTONIC, &now);
	srand((int)now.tv_sec ^ (int)now.tv_nsec);

	w = atoi(argv[1]);
	h = atoi(argv[2]);
	sz = size(w, h);

	fprintf(stderr, "Image size: %dx%d  Array size: %d\n", w, h, sz);

	img = malloc(sz);
	if(img == NULL) {
		perror("Failed to allocate image");
		return 2;
	}

	memset(img, 0, sz);

	fprintf(stderr, "Allocated image at %p\n", img);


	fprintf(stderr, "Drawing a circle\n");
	circle(img, w, h);

	fprintf(stderr, "Writing image to stdout\n");
	fwrite(img, sz, 1, stdout);

	free(img);

	fprintf(stderr, "Goodbye.\n");

	return 0;
}
