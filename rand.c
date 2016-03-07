/*
 * Uses teaching gfx primitives to generate images with random noise.
 * Mar. 7, 2016
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "gfx.h"


int main(int argc, char *argv[])
{
	struct timespec now;
	uint8_t *img;
	int w, h;
	int sz;
	int x, y;

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


	fprintf(stderr, "Setting some pixels\n");
	for(y = 0; y < h; y++) {
		for(x = 0; x < w; x++) {
			setpx(img, w, x, y, rand() % 255);
		}
	}

	fprintf(stderr, "Writing image to stdout\n");
	fwrite(img, sz, 1, stdout);

	free(img);

	fprintf(stderr, "Goodbye.\n");

	return 0;
}
