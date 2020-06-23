ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: main.o songnode.o library.o
	$(CC) -o test_myTunes main.o songnode.o library.o

main.o: main.c songnode.h
	$(CC) -c main.c

songnode.o: songnode.c songnode.h
	$(CC) -c songnode.c

library.o: library.c library.h songnode.h
	$(CC) -c library.c

run:
	./test_myTunes

clean:
	rm *.o
	rm test_myTunes
	rm *~

memcheck:
	valgrind --leak-check=yes ./test_myTunes
