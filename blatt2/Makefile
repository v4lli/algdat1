#CC=/usr/local/Cellar/gcc/7.2.0/bin/gcc-7
CC=g++
CPPFLAGS += -DDEBUG

main: main.cpp Trie.h Makefile
	$(CC) -g -finput-charset=UTF-8 -std=c++11 main.cpp -o main

.PHONY: test debug valgrind
test: main
	./main

debug: main
	lldb ./main

clean:
	rm -f main *.o

valgrind: main
	valgrind --leak-check=full ./main
