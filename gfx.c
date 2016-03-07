/*
 * Teaching basic principles of raster (pixel) graphics.
 * Mar. 6, 2016
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "gfx.h"

// Returns the 1D location in an array of the 2D pixel at (x, y), with an image
// of width w.
int offset(int w, int x, int y)
{
	return x + w * y;
}

// Returns the 1D array size needed to store a 2D image of dimensions w by h.
int size(int w, int h)
{
	return w * h;
}

// Returns the color at the given coordinates in the given image.
uint8_t getpx(uint8_t *img, int w, int x, int y)
{
	return img[offset(w, x, y)];
}

// Sets the color at the given coordinates in the given image.
void setpx(uint8_t *img, int w, int x, int y, uint8_t c)
{
	img[offset(w, x, y)] = c;
}
