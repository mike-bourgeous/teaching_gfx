/*
 * Uses teaching gfx primitives to draw a line.
 * Mar. 27, 2016
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "gfx.h"

// Draws a line on the given image with the given image dimensions, using the
// given coordinates.
void line(uint8_t *img, int w, int h, int x1, int y1, int x2, int y2, uint8_t color)
{
	float x, y;
	float dx, dy;

	dx = fabs(x2 - x1); 
	dy = fabs(y2 - y1); 


	//Always go left to right for horizontal lines and wide diagonals, top to
	//bottom for vertical lines and tall diagonals
	if((x1 > x2 && dx > dy) || (dy >= dx && y1 > y2))
	{
		x = x1; 
		y = y1; 
		x1 = x2; 
		y1 = y2; 
		x2 = x;
		y2 = y; 

	}




	//How to detect if it is a horizontal line
	if(y1 == y2)
	{
		for(x = x1; x <= x2; x++)
		{
			setpx(img, w, x, y1, color);

		}
	}

	else if(x1 == x2)
	{
		for(y = y1; y <= y2; y++)
		{
			setpx(img, w, x1, y, color);
		}
	}

	else if(dx > dy)
	{
		dy = (float)(y2 - y1) / (float)(x2 - x1); 

		for(x = x1, y = y1; x <= x2; x++, y += dy)
		{
			setpx(img, w, x, y, color); 
		}

	}

	else
	{
		dx = (float)(x2 - x1) / (float)(y2 - y1);

		for(x = x1, y = y1; y <= y2; y++, x += dx)
		{
			setpx(img, w, x, y, color);
		}
	}





}

int main(int argc, char *argv[])
{
	struct timespec now;
	uint8_t *img;
	int w, h;
	int sz;
	int num_lines;

	if(argc != 4) {
		fprintf(stderr, "Usage: %s width height num_lines\n", argv[0]);
		return 1;
	}

	// Seed the random number generator to get different results each time
	clock_gettime(CLOCK_MONOTONIC, &now);
	srand((int)now.tv_sec ^ (int)now.tv_nsec);

	w = atoi(argv[1]);
	h = atoi(argv[2]);
	sz = size(w, h);

	fprintf(stderr, "Image size: %dx%d  Array size: %d\n", w, h, sz);
	
	num_lines = atoi(argv[3]); 
	fprintf(stderr, "Line Count: %d\n", num_lines); 

	img = malloc(sz);
	if(img == NULL) {
		perror("Failed to allocate image");
		return 2;
	}

	memset(img, 0, sz);

	fprintf(stderr, "Allocated image at %p\n", img);


	fprintf(stderr, "Drawing some lines\n");

	//Random LINES!
	for(int i = 0; i < num_lines; i++)
	{
		int x1, y1, x2, y2, color; 
		x1 = rand() % w;
		y1 = rand() % h; 
		x2 = rand() % w; 
		y2 = rand() % h; 
		color = rand() % 50; 

		line(img, w, h, x1, y1, x2, y2, color); 
	}

	//****Forward lines****
	//Test horizontal/vertical lines
	line(img, w, h, 0, h / 2, w - 1, h / 2, 148);
	line(img, w, h, w / 2, 0, w / 2, h - 1, 255);

	//Test wide diagonals
	line(img, w, h, 0, 0, w - 1, h / 2, 164);
	line(img, w, h, 0, h - 1, w - 1, h / 2, 164);

	//Test exact diagonals, 45 degrees
	line(img, w, h, 0, 2, 30, 32, 180); 
	line(img, w, h, 0, h - 3, 30, h - 33, 180); 
	
	//Test tall diagonals
	line(img, w, h, 0, 0, w / 2, h - 1, 145);
	line(img, w, h, 0, h - 1, w / 2, 0, 145);

	//****Backward lines***
	//Test horizontal/vertical lines
	line(img, w, h, w / 2, h / 4, 0, h / 4, 160);
	line(img, w, h, w / 4, h / 2, w / 4, 0, 160);

	//Test wide diagonals
	line(img, w, h, w - 1, 0, 0, h / 2, 192);
	line(img, w, h, w - 1, h - 1, 0, h / 2, 192);

	//Test exact diagonals, 45 degrees
	line(img, w, h, w - 1, 2, w - 31, 32, 140); 
	line(img, w, h, w - 1, h - 3, w - 31, h - 33, 140); 
	
	//Test tall diagonals
	line(img, w, h, w - 1, 0, w / 2, h - 1, 180);
	line(img, w, h, w - 1, h - 1, w / 2, 0, 180);



	fprintf(stderr, "Writing image to stdout\n");
	fwrite(img, sz, 1, stdout);

	free(img);

	fprintf(stderr, "Goodbye.\n");

	return 0;
}
