/*
 * Definitions for simple raster (pixel) graphics functions.
 * Mar. 6, 2016
 */
#ifndef GFX_H_
#define GFX_H_

// Returns the 1D location in an array of the 2D pixel at (x, y), with an image
// of width w.
int offset(int w, int x, int y);

// Returns the 1D array size needed to store a 2D image of dimensions w by h.
int size(int w, int h);

// Returns the color at the given coordinates in the given image.
uint8_t getpx(uint8_t *img, int w, int x, int y);

// Sets the color at the given coordinates in the given image.
void setpx(uint8_t *img, int w, int x, int y, uint8_t c);

#endif /* GFX_H_ */
