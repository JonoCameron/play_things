# A very simple Makefile

CC = gcc
CCFLAGS = -I -g -static -lm

main: main.o
	$(CC) -o main main.o $(CCFLAGS)

clean:
	rm -f main *.o
