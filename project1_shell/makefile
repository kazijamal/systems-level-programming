ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: shell.o functions.o
	$(CC) -o test_shell shell.o functions.o

shell.o: shell.c headers.h
	$(CC) -c shell.c

functions.o: functions.c headers.h
	$(CC) -c functions.c

functions.o: functions.c

run:
	./test_shell

testcommands:
	./test_shell < TEST_COMMANDS

clean:
	rm *.o
	rm test_shell
	rm *~

memcheck:
	valgrind --leak-check=yes ./test_shell
