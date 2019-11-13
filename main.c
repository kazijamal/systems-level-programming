#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

struct stat file;

int main() {
  stat("testfile.txt", &file);

  printf("Displaying metadata of file testfile.txt\n\n");

  printf("File size in bytes: %ld\n", file.st_size);

  printf("File mode (permissions): %d\n", file.st_mode);

  printf("Time of last access: %s", ctime(&(file.st_atime)));
  
  return 0;
}
