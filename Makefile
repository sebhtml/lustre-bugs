CC=gcc
CFLAGS=-Wall  -O3 -march=native 
#-D_POSIX_C_SOURCE=200809L
# -std=c99

all: signal-bug

signal-bug: signal-bug.c
	$(CC) $(CFLAGS) signal-bug.c -o signal-bug

test: all
	./signal-bug

clean:
	rm signal-bug
