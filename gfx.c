/*
 * Teaching basic principles of raster (pixel) graphics.
 * Mar. 6, 2016
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Returns the 1D location in an array of the 2D pixel at (x, y), with an image
// of width w.
int offset(int x, int y, int w)
{
	return x + w * y;
}

// Returns the 1D array size needed to store a 2D image of dimensions w by h.
int size(int w, int h)
{
	return w * h;
}

int main(int argc, char *argv[])
{
	uint8_t *img;
	int w, h;
	int sz;
	int x, y;

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

	free(img);

	fprintf(stderr, "Goodbye.\n");

	return 0;
}
