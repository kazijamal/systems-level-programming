all: main.o fxn.o
	gcc -o program main.o fxn.o

main.o: main.c header.h
	gcc -c main.c

fxn.o: fxn.c
	gcc -c fxn.c

run:
	./program

clean:
	rm *.o
	rm *~
