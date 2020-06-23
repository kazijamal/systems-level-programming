ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

<<<<<<< HEAD
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
=======
all: main.o
	$(CC) -o test_stat main.o -lm

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
>>>>>>> stat/master
