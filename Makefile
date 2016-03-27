.PHONY: all

all: rand circle grad line

rand: rand.c gfx.c Makefile
	colorgcc -Wall -Wextra -O2 rand.c gfx.c -o rand

circle: circle.c gfx.c Makefile
	colorgcc -Wall -Wextra -O2 circle.c gfx.c -o circle -lm

grad: grad.c gfx.c Makefile
	colorgcc -Wall -Wextra -O2 grad.c gfx.c -o grad

line: line.c gfx.c Makefile
	colorgcc -Wall -Wextra -O2 line.c gfx.c -o line
