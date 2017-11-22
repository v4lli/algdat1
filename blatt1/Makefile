#CC=/usr/local/Cellar/gcc/7.2.0/bin/gcc-7
CC=g++

cursor:
	$(CC) -g -c -std=c++11 CursorMain.cpp -o CursorMain.o
	$(CC) -g -o cursormain CursorMain.o -o cursormain

main:
	$(CC) -g -std=c++11 -DDEBUG=true Student.cpp Main.cpp -o blatt1
	./blatt1

clean:
	rm -f cursormain *.o

test: cursor
	./cursormain

debug: cursor
	lldb ./cursormain
