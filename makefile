ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: main.o
	$(CC) -o test_stat main.o

main.o: main.c
	$(CC) -c main.c

run:
	./test_stat

clean:
	rm *.o
	rm test_stat
	rm *~

memcheck:
	valgrind --leak-check=yes ./test_stat
