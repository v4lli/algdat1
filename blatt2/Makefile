#CC=/usr/local/Cellar/gcc/7.2.0/bin/gcc-7
CC=g++

main: main.cpp Trie.h
	$(CC) -g -std=c++11 main.cpp -o main

test: main
	./main

clean:
	rm -f main *.o
