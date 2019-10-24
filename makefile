all: main.o fxn.o
	gcc -o test_list main.o fxn.o

main.o: main.c header.h
	gcc -c main.c

fxn.o: fxn.c header.h
	gcc -c fxn.c

run:
	./test_list

clean:
	rm *.o
	rm test_list
	rm *~
