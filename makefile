ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: main.o songnode.o
	$(CC) -o test_myTunes main.o songnode.o

main.o: main.c songnode.h
	$(CC) -c main.c

songnode.o: songnode.c songnode.h
	$(CC) -c songnode.c

run:
	./test_myTunes

clean:
	rm *.o
	rm *~

memcheck:
	valgrind --leak-check=yes ./test_list
