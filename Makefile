CC = gcc
CFLAGS = -std=c23 -Wall -O2
NIM = nim
NIMFLAGS = c -d:release

all: sort_program

sort_program: bubble_str bubble_num sort_nim

bubble_str: bubble_str.c
	$(CC) $(CFLAGS) -o bubble_str bubble_str.c

bubble_num: bubble_num.c
	$(CC) $(CFLAGS) -o bubble_num bubble_num.c

sort_nim: sorting_algorithms.nim
	$(NIM) $(NIMFLAGS) -o:sorting_algorithms sorting_algorithms.nim

clean:
	del bubble_str.exe bubble_num.exe sorting_algorithms.exe

.PHONY: all clean