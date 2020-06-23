ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: main.o
	$(CC) -o test_randfile main.o

main.o: main.c
	$(CC) -c main.c

run:
	./test_randfile

clean:
	rm *.o
	rm test_randfile
	rm randfile
	rm *~

memcheck:
	valgrind --leak-check=yes ./test_randfile
