# A very simple Makefile

CC = g++
CCFLAGS = -I -g -static
CXXFLAGS = -std=gnu++17

main: hello_world.o
	$(CC) $(CXXFLAGS) -o main hello_world.o

clean:
	rm -f main *.o
