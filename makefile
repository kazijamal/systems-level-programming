ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

ifdef ($(VAR))
	RUN = ./test_dirinfo $(VAR)
else
	RUN = ./test_dirinfo
endif

all: main.o
	$(CC) -o test_dirinfo main.o

main.o: main.c
	$(CC) -c main.c

run:
	$(RUN)

clean:
	rm *.o
	rm test_dirinfo
	rm *~

memcheck:
	valgrind --leak-check=yes ./test_dirinfo
