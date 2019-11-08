# systems-work

## Friday 11/8/19

### umask - <sys/stat.h>
- set the file creation permission mask
- by default, created files are not given the exact permissions provided in the mode argument to open; some permissions are automatically shut off
- default Linux mask is 002
- umask is applied the folloing way:
```sh
new_permissions = ~mask & mode
```
### read - <unistd.h>
- read data from a file
```c
read(fd, buff, n)
```
- read `n` bytes from `fd`'s file into `buff`
- returns the number of bytes actually read; returns -1 and sets errorno if unsuccessful
- `buff` must be a pointer
### write - <unistd.h>
- read data from a file
```c
write(fd, buff, n)
```
- write `n` bytes to `fd`'s file from `buff`
- returns the number of bytes actually written; returns -1 and sets errorno if unsuccessful
- `buff` must be a pointer

### close
```c
close(fd)
- returns 0 if successful, 1 if unsuccessful
```

## Thursday 11/7/19

### file tables
- a list of all files being used by a program while it is running
- contains basic information like the file's location and size
- the file table has limited space, which is a power of 2 and commonly 256
- `getdtablesize()` will return the file table size
- each file is given an integer index, starting at 0, this is the file descriptor
- there are 3 files always open in the table:
	- 0 or STDIN_FILENO: stdin
	- 1 or STDOUT_FILENO: stdout
	- 2 or STDERR_FILENO: stderr

| FD | Name      | Path      | Size ... |
|----|-----------|-----------|----------|
|  0 | stdin     |           |          |
|  1 | stdout    |           |          |
|  2 | stderr    |           |          |
|  3 |           |           |          |
|  4 |           |           |          |
### open - <fcntl.h>
- add a file to the file table and returns its file descriptor
- if open fails, -1 is returned, extra error information can be found in `errno`
	- `errno` is an int variable that can be found in <errno.h>
	- use `strerror` (in string.h) on errno to terun a string description of the error
```c
open(path, flags, mode)
```
- `mode`
	- only used when creating a file; set the new file's permissions using a 3 digit octal #
- `flags`
	- determine what you plan to do with the file, use the following constants and combine with |:
		- O_RDONLY
		- O_WRONLY
		- O_RDWR 
		- O_APPEND
		- O_TRUNC 
		- O_CREAT
		- O_EXCL: when combined with O_CREATE< will return an error if the file exists

## Wednesday 11/6/19

### file permissions (mode)
- 3 types of permissions
	- read, write, execute
- permissions can be represented as 3-digit binary #s, or 1-digit octal #s
	- 100 <==> 4 => read only
	- 111 <==> 7 => read, write, execute
- there are 3 permission "areas"
	- user (owner), group, others
	- membership in each area is mutually exclusive
	- the creator of the file is the default setting for the user and group of a file
```sh
chmod permissions file
```
- command line utility to change file permissions
- the owner of a file (or root) can change permissions
- file ownership and group can be changed with the `chown` and `chgrp` command line utilities

## Monday 11/4/19

### binary, octal and hexadecimal integers
- other base formatting characters for `printf`:
```
%o: octal integer
%x: hexadecimal integer
```
- you can define native integers in base 2, 8 and 16 by using the following
```
0b : binary
0 : octal
0x : hexadecimal
```
### bitwise operators
evaluated on every bit of a value

`~x`
- Negation: flip every bit of x

`a | b`
- Bitwise or: perform logical or for each pair of bits in (a, b)

`a & b`
- Bitwise and: perform logical and for each pair of bits in (a, b)

`a ^ b`
- Bitwise or

### swapping two variables using bitwise operators
```c
a = a^b
b = a^b
a = a^b

r = a^bt
b = r^b => a^(b ^ b)
a = a^b
```

## Monday 10/28/19

### makefile updates
#### variables
```make
CC = gcc -g			sets the value of the variable CC
$(CC)				returns the value of the variable CC
```
#### conditional statements
```make
ifeq ($(DEBUG), true)		if the DEBUG variable equals true
	CC = gcc -g
else
	CC = gcc
endif
```
- this lets the user do `make DEBUG=true`

## Thursday 10/24/19

### Get 'Dem Bugs
#### GDB - GNU DeBugger
- to use gdb, you must compile using the -g flag with gcc
- basic usage: 
```console
$ gdb program
```
- this starts a gdb shell from which you can run your program
- commands from in the gdb shell:
	- `run`: runs the program until it ends/crashes/gets a signal
	- `list`: show the lines of code run around a crash
	- `print var`: print the value of `var`
	- `backtrace`: show the current stack
	- `break line number`: creates breakpoint at a line
- running a program in pieces
	- `run`: restarts the program
	- `continue`: run the program until the next breakpoint/crash/end
	- `next`: run the next line of the program only
	- `step`: run the next lne of the program, if that is a funcxtion call, run only the next line of that function
#### Valgrind
- tool for debugging memory issues in C programs
- you must compile with -g in order to use valgrind (and similar tools)
- usage:
```console
$ valgrind --leak-check=yes ./program
```

## Wednesday 10/23/19

### Dynamic Memory Allocation continued
#### calloc
```c
calloc(site_t n, size_t x)
```
- allocates n * x bytes of memory, ensuring every bit is 0
#### realloc
```c
realloc(void *p, size_t x)
```
- changes the amount of memory allocated for a block to `x` bytes
- `p` must point to the beginning of a block
- returns a pointer to the beginning of the block (this is not always the same as `p`)
- if `x` is smaller than the original size of the allocation, the extra bytes will be released
- if `x` is larger than the original size then either:
	1. if there is enough space at the end of the original allocation, the original allocation will be updated
	2. if there is not enough space, a new allocation will be created, containing all the original values; the original allocation will be freed

## Tuesday 10/22/19

### Dynamic Memory Allocation
#### malloc
```c
malloc(site_t x)
```
- allocates x bytes of heap memory
- returns the address at the beginning of the allocation
- returns a `void *`
```c
int *p;
p = malloc(5 * sizeof(int));
```
#### free
```c
free(void * p)
```
- releases dynamically allocated memory
- has one parameter, a pointer to the beginning ofa  dynamically allocated block of memory
- every call to `malloc` or `calloc` should have a corresponding call to `free`

## Monday 10/21/19

### Stack memory vs Heap memory
- every program can have its own stack and heap

### Stack Memory
- stores all normally declared variables (including pointers and structs), arrays and function calls
- functions are pushed onto the stack in the order they are called, and popped off when completed
- when a function is popped off the stack, the stack memory associated with it is released

### Heap Memory
- stores dynamically allocated memory
	- dynamically allocated memory is allocated at runtime
- data will remain in the heap until it is manually released (or the program terminates)

## Tuesday 10/15/19

### Struct
- create a new type that is a collection of values
```c
struct { int a; char x; } s;
```
- here, s is a variable of type `struct {int a; char x; }`
- we use the . operator to access a value inside a struct
```c
s.a = 10;
s.x = '@';
```
- the size of the struct does not have to equal to the sum of the sizes of its values
```c
struct foo { int a; char x; }; // struct prototype
```
- struct prototypes make it easier to create multiple variables of the same type, and also helps with interaction between those variables
- normally structs are declared outside of the main function or in header files to increase scope
- . binds before * (dot operator has precedence newover dereference operator)
- to access data from a struct pointer you would do:
```c
struct foo *p;
p = &s;
(*p).x;
p->x; // c shorthand for (*p).x
```

## Thursday 10/10/19

### typedef
- a way to provide a new name for an existing type
- this can be useful so that the same source code is portable to different systems
- also makes the source code more readable with more descriptive new names
- eg. size_t is a different name for an unsigned long
```c
typedef real_type new_name;
typedef unsigned long size_t;
size_t x = 139; // x is really an unsigned long
```

## Tuesday 10/08/19

### make
- tool to make executables
- works with any language
- just an automation tool, can be used for other things
- javac creates byte code or binary code which is then run by the jvm (not an executable)
- automates checking of dependencies and makes working with multi file programs easier
new
### makefile
- only recompiles modified files
- good practices
  - make a separate compilation step for each .c file with .o as the target
    - dependencies should only be the .c file and its corresponding headers or .h files
  - dependencies of the all target should be all of the .o files
  - have targets that serve similar purposes to run and clean
- example
```
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
	rm program
        rm *~
```

## Friday 10/04/19 

### Primitive Types and Byte Size
| Primitives | Byte Size |
|------|-|
|char  |1|
|short |2|
|int   |4|
|long  |8|
|float |4|
|double|8|
 
### Pointers
- variable types for storing memory addresses
- unsigned integers of 8 bytes (unless more specialized)
- stores a memory address (integer) that fits in 8 bytes or less 
- pointers can point to pointers 
- the reason for pointers being 8 bytes large is a combination of os and hardware restrictions 

### CPU
- things go into a CPU (instructions or data)
  - instructions (e.g. add next two values to come in, copy next value to memory location)
  - several inputs are fed in at once/all read at same time 
  - each input is a bit
  - as standard, 64 bits (8 bytes) come in at a time 
    
- CPU outputs a result
  - 2 gigahertz CPU - runs 2 billion cycles per second

- processor must be able to read memory address in one input 
  - thus pointers are 8 bytes in 64 bit processer machines 
  - size of the pointer will depend on the size of the processing available    
  - running same program on different computers may result in different pointer sizes 
  - there are 2^64 theoretical memory addresses 

```
int x; // in memory, x refers to a 4 byte chunk (for example purposes, the address is 2000)
int *p; // in memory, p refers to an 8 byte chunk (for example purposes, theg address is 2010)
x = 12; // the value 12 is assigned to x

// uninitialized pointers point to unknown memory address

p = 51; 
// assigning a literal value to a pointer is a bad idea
// points to memory address 51. (get a segmentation error probably)
// only literal value  that is viable is 0 -> points to null

p = &x; (address of x)
// p has a value of 2000; 
/ /p points to x;

*p = 6; //at memory location 2000, the value is now 6; 
// * is the dereference operator which means go to this location and interact with the value

// functions get own memory address space and every parameter is copied (not used outside of function scope)
// pointers as parameters 
def foo(int *f) {
    *f = 10;
}

foo(p)
// new variable f is made in the memory space for foo 
// f is a copy of p
// value of f is 2000 
// f has its own memory address (20)

// you can modify a primitive if you have its address

// adding one to the int pointer variable adds 4 to the memory address (because an int is 4 bytes)
```

## Thursday 10/03/19

### Java
- .java -> .class -> JVM -> OS -> hardware

### C
- .c -> executable -> OS -> hardware

### Protected Memory
- OS allocates memory for programs and keeps track
- programs cannot access memory outside of their allocation

### Segmentation Fault
- occurs when a program is trying to access a segment of memory that it should not

### Strings and Pointers
```
char *p; pointer
char s0[6]; memory address 
p = s0; p now points to the start of the s0 array 
char s0[6] = "hello"; [h][e][l][l][o][0] // this is a mutable piece of memory but another immutable literal is made 
p = s0; // points to the mutable string 
p[0] = 'j'; // mutable string is changed 
p = "hello" //now points to the immutable literal
```
