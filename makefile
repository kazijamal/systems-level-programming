ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: main.o
	$(CC) -o test_shell main.o

main.o: main.c
	$(CC) -c main.c

run:
	./test_shell

clean:
	rm *.o
	rm test_shell
	rm *~

memcheck:
	valgrind --leak-check=yes ./test_shell
