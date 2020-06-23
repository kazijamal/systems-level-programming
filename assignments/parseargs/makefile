<<<<<<< HEAD
all: main.o fxn.o
	gcc -o program main.o fxn.o

main.o: main.c header.h
	gcc -c main.c

fxn.o: fxn.c header.h
	gcc -c fxn.c

run:
	./program

clean:
	rm *.o
	rm *~
=======
ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: main.o
	$(CC) -o test_parseargs main.o

main.o: main.c
	$(CC) -c main.c

run:
	./test_parseargs

clean:
	rm *.o
	rm test_parseargs
	rm *~

memcheck:
	valgrind --leak-check=yes ./test_parseargs
>>>>>>> parseargs/master
