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
	uint8_t *img;
	int w, h;
	int sz;
	int x, y;
	int c;

	if(argc != 3) {
		fprintf(stderr, "Usage: %s width height\n", argv[0]);
		return 1;
	}

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


	fprintf(stderr, "Drawing some gradient stripes\n");
	for(y = 0, c = 0; y < h; y++) {
		for(x = 0; x < w; x++) {
			setpx(img, w, x, y, c);
			c++;
			c &= 0xff;
		}
	}

	fprintf(stderr, "Writing image to stdout\n");
	fwrite(img, sz, 1, stdout);

	free(img);

	fprintf(stderr, "Goodbye.\n");

	return 0;
}
