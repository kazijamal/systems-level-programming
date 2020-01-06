# systems-work

## Friday 1/3/20

When writing a multi-program project with interprogram communication, figuring out those connections is important!

- Peer-to-peer-program
  - Client 0 will wait for other client to say hello and then send a message
  - Direct connection between clients
  - Good for well structured interactions (e.g. turn-based games)
  - peer-to-peer format with more than 2 players may get harder to manage

- Single Server
  - One server handles all connections and all communications.
  - Client sends input, waits for something to resposnd, and server sends something back
  - Can be implemented using pipes or sockets
  - Server needs to know which client it responds to and which client it is receiving information from
  - Good for real-time components that are not structured (e.g. chats)
  - One server can get bogged down with a lot of connections

- Forking Server
  - Standardly used in file servers, ssh, etc.
  - One main server exists but is fairly specialized
    - Handles all connections
    - Does not handle communication
    - Creates a new subserver to handle all communication
  - Main server receives initial communication, forks a new subserver. The subserver sends a resposne to the client. Main server connection is severed from the client. Subservers are disconnected from main server
  - Cannot communicate between clients or subservers once connections are severed.

- Dispatch Server
  - One main server
    - Handles all connections
    - Handles all incoming data from clients
    - Subservers handle all outgoing data to clients
    - Routes messages to appropriate subservers
  - Main server has array of pipes that connect to subservers

## Wednesday 12/18/19

### semaphores
- created by Edsger Dijkstra
- IPC construct used to control access to a shared resource (like a file or shared memory)
- most commonly, a semaphore is used as a counter representing how many processes can access a resource at a given time
	- if a semaphore has a value of 3, then it can have 3 active "users"
	- if a semaphore has a value of 0, then it is unavailable
- most semaphore operations are "atomic", meaning they will not be split up into multiple processor instructions

### semaphore operations
- create a semaphore
- set an initial value
- remove a semaphore
- Up(S) / V(S) - atomic
	- release the sempahore to signal you are done with its associated resource
	- pseudocode
		- `S++`
- Down(S) / P(S) - atomic
	- attempt to take the semaphore
	- if the semaphore is 0, wait for it to be available
	- pesudocode
		- `while (S == 0) { block } S--;`

## Tuesday 12/17/19

```c
int main() {
  int shmd;
  char * data;
  char input[3];
  
  shmd = shmget(KEY, SEG_SIZE, IPC_CREAT | 0644); //usually 0600
  data = shmat(shmd, 0, 0);
  
  if(!(*data))
    printf("New segment, no data to display\n");
  else 
    printf("Current contents: [%s]\n", data);
  
  printf("Would you like to modify the segment?(y/n) ");
  fgets(input, 3, stdin);
  
  if(input[0] == 'y') {
    printf("Enter new data: ");
    fgets(data, SEG_SIZE, stdin);
    *strchr(data, '\n') = 0;
    printf("Current contents: [%s]\n", data);
  }
  
  shmdt(data); // detach pointer from variable 
  
  printf("Would you like to remove the segment?(y/n) ");
  fgets(input, 3, stdin);
  
  if(input[0] == 'y') {
    shmctl(stmd, IPC_RMID, 0);
    printf("segment deleted\n");
  }
}
```

### concurrency problems
- several programs can used shared memories at the same time and you could delete data that another program is using
- two concurrent programs can write to a file but two write processes might get mixed up in the processor, writing interweavedly

## Monday 12/16/19

### shared memory

- `<sys/shm.h>, <sys/ipc.h>, <sys/types.h>`
- a segment of heap memory that can be accessed by multiple processes.
- shared memory is accessed via a key that is known by any process that needs to access it.
- shared memory does not get released when a program exits.
- 5 shared memory operations
  - create the segment (happens once) - `shmget`
  - access the segment (happens once per process) - `shmget`
  - attach the segment to a variable (once per process) - `shmat`
  - detach the segment from a variable (once per process) - `shmdt`
  - remove the segment (happens once) - `shmctl`

```c
#include <sys/ipc.h>

#define KEY 24601

int main() {
  int * data;
  int shmd;

  shmget(KEY, sizeof(int), IPC_CREAT | 0640);
  printf("shmd: %d\n"); // 131072

  data = shmat(shmd, 0, 0);

  printf("*data: %d\n", *data); // 0
  *data = *data + 10;
  printf("*data: %d\n", *data); // 10

  shmdt(data); // shared memory still exists but pointer is removed
  printf("*data: %d\n", *data); // segmentation fault

  return 0;
}
```

`ipcs -m`
`ipcrm -m MEM_KEY`

## Thursday 12/12/19

### named pipes
- FIFOs
- same as unnamed pipes except FIFOs have a name that can be used to identify them via different programs
- like unnamed pipes, FIFOs are unidirectional
- `mkfifo`
	- shell command to make a FIFO
	
### mkfifo - <sys/types.h> <sys/stat.h>
- c function to create a FIFO
- returns 0 on success and -1 on failure
- once created, the FIFO acts like a regular file, and we can use open, read, write, and close on it
- FIFOs will block on open until both ends of the pipe have a connection

## Wednesday 12/11/19

### pipe
- a conduit between 2 separate processes on the same computer
- pipes have 2 ends, a read end and a write end
- pipes act just like files (i.e. you can `read()` and `write()` to send any kind of data)
- pipes exist in memory
- unnamed pipes have no external identifier

### pipe - <unistd.h>
- create an unnamed pipe
- returns 0 if the pipe was created, -1 if not
```c
pipe(descriptors)
```
- `descriptors`
	- array that will contain the descriptors for each end of the pipe; must be an int array of size 2
	- `descriptors[0]` is the read end
	- `descriptors[1]` is the write end

## Friday 12/6/19

### file redirection
- changing the usual input/output behavior of a program
- command line redirection
```sh
>
```
- redirects `stdout` to a file
- overwrites the contents of the file
```sh
>>
```
- redirects `stdout` to a file by appending
```sh
2>
```
- redirects `stderror` to a file
- overwrites the file (`2>>` appends)
```sh
&>
```
- redirects `stdout` and `stderror`
- overwrites the file (`&>>` appends)

### command line redirection
```sh
<
```
- redirect `stdin`from a file

### dup2 - <unistd.h>
```c
dup2(fd1, fd2)
```
- redirects `fd2` to `fd1`
- any use of `fd2` will now act on the file for `fd1`

### dup - <unistd.h>
```c
dup(fd)
```
- duplicates an existing entry in the file table
- returns a new file description for the duplicate entry

## Monday 12/2/19

### wait() - <sys/wait.h>
- stops a parent process from running until any child has exited
- returns the pid of the child that exited, or -1 (errno), and gathers information about the child process (this is called raping)
- if multiple child processes exit, an arbitrary one will be reaped
```c
wait(status)
```
- status macros
	- usage: `MACRO(status)`
	- `WIFEXITED`: true if child exited normally
	- `WEXITSTATUS`: the return value of the child
	- `WIFSIGNALED`: true if child exited due to a signal
	- `WTERMSIG`: the signal number intercepted by the child

## Wednesday 11/27/19

### fork() - <unistd.h>
- creates a separate process based on the current one, the new process is called a child, the original is the parent
- the child process is a duplicate of the parent process
- all parts of the parent process are copied, including stack and heap memory, and the file table
- returns 0 to the child and the child's pid or -1 (errno) to the parent

## Tuesday 11/26/19

### strsep - <string.h>
- parse a string with a common delimiter
```c
strsep(source, delimiters)
```
- locates the first occurrence of any of the specified `delimiters` in a string and replaces it with `NULL`
- `delimiters` is a string, each character is interpreted as a distinct delimiter
- returns the beginning of the original string, sets `source` to the string starting at 1 index past the location of the new `NULL`
- 
example:
```c
char line[100] = "woah-this-is-cool";
char *curr = line;
char * token;
token = strsep(&curr, "-");
```
- replaces the `-` after "woah" with `NULL`
- returns a pointer to the `w` in "woah"
- sets `curr` to point to the t in "this is cool"

## Monday 11/25/19

### the `exec` family - <unistd.h>
- a group of c functions that can be used to run other programs
- replaces the current process with the new program
```c
execl(path, command, arg0, arg1 ... NULL)
```
- `path`
	- the path to the program (ex: `"/bin/ls"`)
- `command`
	- the name of the program (ex: `"ls"`)
- `arg0 ...`
	- each command line argument you wish to give the program (ex: `"-a"`, `"-l"`)
	- the last argument must be `NULL`
```c
execlp(path, command, arg0, arg1 ... NULL)
```
- works like `execl`, except it uses the $PATH environment variable for command
```c
execvp(path, argument_array)
```
- `argument_array`
	- array of strings containing the arguments to the command
	- `argument_array[0]` must be the name of the program
	- last entry must be NULL

## Friday 11/22/19

### signal handling in c programs - <signal.h>
`sighandler`
- to intercept signals in a c program you must create a signal handling function
- some signals (like SIGKILL, SIGSTOP) cannot be caught
```c
static void sighandler(int signo)
```
- must be `static`, must be `void`, must take a single `int` parameter
- `static`
	- static values in c exist outside hte normal call stack, they can be accessed regardless of the function at the top
	- for variables, this also means they retain their value even if the function they are declared in has ended
	- static values (variables and functions) can only be accessed from within the file they are declared (unlike global values)

## Thursday 11/21/19

### signals
- limited way of sending information to a process
- sends an integer value to a process
```sh
$ kill
```
- command line utility to send a signal to a process
```sh
$ kill pid
```
- sends signal 15 (`SIGTERM`) to `pid`
```sh
$ kill -signal pid
```
- sends `signal` to `pid`
```sh
$ killall [-signal] process_name
```

### signals in c programs - <signal.h>
```c
kill(pid, signal)
```

## Wednesday 11/20/19

### processes
- every running program is a process
- a process can create subprocesses, but these are no different from regular processes
- a processor can handle 1 process per cycle (per core)
- "multitasking" appears to happen because the processor switches between all the active processes quickly

## Tuesday 11/19/19

### sscanf - <stdio.h>
- reads in data from a string using a format string to determine types
```c
sscanf(char *s, char * format, void * var0, void * var1, ...)
```
- copies the data into each variable

example:
```c
int x; float f; double d;
sscanf(s, "%d %f %lf", &x, &f, &d);
```

## Monday 11/18/19

### command line arguments
```c
int main(int argc, char *argv[])
```
- program name is considered the first command line argument
- `argc`
	- number of command line arguments
- `argv`
	- array of command line arguments as strings

### fgets - <stdio.h>
- read in data from a file stream and store it in a string
```c
fgets(char * s, int n, FILE * f);
```
- reads at most `n`-1 characters from **file stream** `f` and stores it in `s`, appends NULL to the end
- stops at newline, end of file, or the byte limit
- file stream
	- `FILE *` type, more complex than a file descriptor, allows for ***buffered*** input
	- `stdin` is a `FILE *` variable
	
example:
```c
fgets(s, 100, stdin)
```

## Thursday 11/14/19

### directories
- a linux directory is a file containing the names of the files within the directory along with basic information, like file typehow
- all directories have a size of 4096 bytes, no matter its contents (on Linux machines)
- executable; allows to `cd` into a directory
- moving a file is much faster than copying a file because you are just deleting from one directory file and adding to another when moving a file, compared to duplicating the file and writing data when copying a file
### opendir - <dirent.h>
- opens a directory file
- this will not change the current working directory (cwd), it only alopendir(path)
lows your program to read the contents of the directory file
```c
```
- returns a pointer to a directory stream (`DIR *`)
### readdir - <dirent.h>
```c
readdir(dir_stream)
```
- returns a pointer to the next entry in a directory stream, or NULL if all entries have already been returned
- `struct dirent` - <sys/types.h>

## Wednesday 11/13/19

### stat - <sys/stat.h>
- get information about a file (metadata)
	- as storage got cheaper and operating systems got faster, more metadata exists
	- for text files, metadata contains hash tables for the contents of the file, allowing for searches to return relevant returns based on content queries
```c
stat(path, stat_buffer)
```
- `stat_buffer`
	- must be a pointer to a `struct stat`
	- all the file information gets put into the stat buffer
	- some of the fields in `struct stat`
		- `st_size`
			- file size in bytes
		- `st_uid`, `st_gid`
			- user id, group id
		- `st_mode`
			- file permissions of int type
		- `st_atime`, `st_mtime`
			- last access, last modification
			- these are `time_t` variables; we can use functions in `time.h` to make sense of them
				- `ctime(time)` returns a string based on time variable

## Tuesday 11/12/19

### lseek - <unistd.h>
- set the current position in an open file
```c
lseek(file_description, offset, whence)
```
- `offset`
	- the number of bytes to move the position by; can be negative
- `whence`
	- where to measure the offset from
		- SEEK_SET
			- offset is evaluated from the beginning of the file
		- SEEK_CUR
			- offset is relative to the current position in the file
		- SEEK_END
			- offset is evaluated from the end of the file
	- returns the number of bytes the current position is from the beginning of the file, or -1 (errno)

## Friday 11/8/19

### umask - <sys/stat.h>
- set the file creation permission mask
- by default, created files are not given the exact permissions provided in the mode argument to open; some permissions are automatically shut off
- default Linux mask is 002
- umask is applied the following way:
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
- write data to a file
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
		- O_EXCL: when combined with O_CREAT will return an error if the file exists

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
