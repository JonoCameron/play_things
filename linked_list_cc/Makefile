# A very simple Makefile

CC = g++
CCFLAGS = -I -g -static
CXXFLAGS = -std=gnu++17

main: main.o LL.o
	$(CC) $(CXXFLAGS) -g -o main main.o LL.o

clean:
	rm -f main *.o
