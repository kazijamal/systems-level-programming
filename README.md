# systems-work

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

### Make
- tool to make executables
- works with any language
- just an automation tool, can be used for other things
- javac creates byte code or binary code which is then run by the jvm (not an executable)
- automates checking of dependencies and makes working with multi file programs easier

### makefile
- only recompiles modified files
- good practices
  - make a separate compilation step for each .c file with .o as the target
    - dependencies should only be the .c file and its corresponding hearders or .h files
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
