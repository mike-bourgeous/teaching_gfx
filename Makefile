.PHONY: all debug clean

CFLAGS=-Wall -Wextra -g -std=c99 -D_XOPEN_SOURCE=700
CC=gcc

all: rand circle grad line sdl_test

debug:
	$(CC) $(CFLAGS) -O0 rand.c gfx.c -o rand
	$(CC) $(CFLAGS) -O0 circle.c gfx.c -o circle -lm
	$(CC) $(CFLAGS) -O0 grad.c gfx.c -o grad
	$(CC) $(CFLAGS) -O0 line.c gfx.c -o line
	$(CC) $(CFLAGS) -O0 sdl_test.c -lSDL2 -o sdl_test

clean:
	rm -f rand circle grad line sdl_test

rand: rand.c gfx.c Makefile
	$(CC) $(CFLAGS) -O2 rand.c gfx.c -o rand

circle: circle.c gfx.c Makefile
	$(CC) $(CFLAGS) -O2 circle.c gfx.c -o circle -lm

grad: grad.c gfx.c Makefile
	$(CC) $(CFLAGS) -O2 grad.c gfx.c -o grad

line: line.c gfx.c Makefile
	$(CC) $(CFLAGS) -O2 line.c gfx.c -o line

sdl_test: sdl_test.c
	$(CC) $(CFLAGS) -O2 sdl_test.c -lSDL2 -o sdl_test
