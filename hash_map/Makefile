# A very simple Makefile

CC = g++
CCFLAGS = -I -g -static
CXXFLAGS = -std=gnu++17

main: hash_map.o hashmap_library.o
	$(CC) $(CXXFLAGS) -o main hash_map.o hashmap_library.o

clean:
	rm -f main *.o
