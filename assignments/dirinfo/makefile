ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: main.o
	$(CC) -o test_dirinfo main.o

main.o: main.c
	$(CC) -c main.c

run:
	./test_dirinfo

clean:
	rm *.o
	rm test_dirinfo
	rm *~

memcheck:
	valgrind --leak-check=yes ./test_dirinfo
