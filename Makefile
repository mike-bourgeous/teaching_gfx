.PHONY: all debug

CFLAGS=-Wall -Wextra -g -std=c99 -D_XOPEN_SOURCE=700

all: rand circle grad line

debug:
	gcc $(CFLAGS) -O0 rand.c gfx.c -o rand
	gcc $(CFLAGS) -O0 circle.c gfx.c -o circle -lm
	gcc $(CFLAGS) -O0 grad.c gfx.c -o grad
	gcc $(CFLAGS) -O0 line.c gfx.c -o line

rand: rand.c gfx.c Makefile
	gcc $(CFLAGS) -O2 rand.c gfx.c -o rand

circle: circle.c gfx.c Makefile
	gcc $(CFLAGS) -O2 circle.c gfx.c -o circle -lm

grad: grad.c gfx.c Makefile
	gcc $(CFLAGS) -O2 grad.c gfx.c -o grad

line: line.c gfx.c Makefile
	gcc $(CFLAGS) -O2 line.c gfx.c -o line
