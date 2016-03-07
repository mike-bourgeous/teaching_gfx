.PHONY: all

all: gfx

gfx: gfx.c
	colorgcc -Wall -Wextra -O2 gfx.c -o gfx
