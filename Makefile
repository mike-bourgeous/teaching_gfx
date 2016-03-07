.PHONY: all

all: rand

rand: rand.c gfx.c
	colorgcc -Wall -Wextra -O2 rand.c gfx.c -o rand
