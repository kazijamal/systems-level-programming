all: main.o fxn.o
	gcc -o test_list main.o fxn.o

main.o: main.c header.h
	gcc -c -g main.c

fxn.o: fxn.c header.h
	gcc -c -g fxn.c

run:
	./test_list

clean:
	rm *.o
	rm test_list
	rm *~

valgrind:
	valgrind --leak-check=yes ./test_list
