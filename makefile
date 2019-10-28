ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: main.o fxn.o
	$(CC) -o test_list main.o fxn.o

main.o: main.c header.h
	$(CC) -c main.c

fxn.o: fxn.c header.h
	$(CC) -c fxn.c

run:
	./test_list

clean:
	rm *.o
	rm *~

memcheck:
	valgrind --leak-check=yes ./test_list
