# A very simple Makefile

CC = gcc
CCFLAGS = -I -g -static

hello_world: hello_world.o main.o
	$(CC) -o hello_world hello_world.o main.o

clean:
	rm -f hello_world *.o
