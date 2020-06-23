#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

// generates a random number by reading in the correct number of bytes from /dev/random

unsigned int rand_num() {
  int return_val;
  
  int rand_fd = open("/dev/random", O_RDONLY);
  if (rand_fd == -1) {
    printf("\nopen: %s\n", strerror(errno));
  }

  unsigned int ans;
  return_val = read(rand_fd, &ans, sizeof(int));
  if (return_val == -1) {
    printf("\nread: %s\n", strerror(errno));
  }
  
  return_val = close(rand_fd);
  if (return_val == 1) {
    printf("\nclose: Unsuccessful\n");
  }

  return ans;
}

int main() {
  int return_val;
  
  // populates an array with 10 random numbers generated by rand_num() and prints out each value
  
  unsigned int rand_array[10];
  int i;
  printf("Generating random numbers:\n");
  for (i = 0; i < 10; i++) {
    rand_array[i] = rand_num();
    printf("\trandom %d: %u\n", i, rand_array[i]);
  }
  
  // writes the array to a file without using a loop

  umask(0);
  int write_fd = open("randfile", O_WRONLY | O_CREAT | O_EXCL, 0666);
  if (write_fd == -1) {
    printf("\nopen: %s\n", strerror(errno));
  }

  printf("\nWriting numbers to file...\n");
  return_val = write(write_fd, rand_array, sizeof(int) * 10);
  if (return_val == -1) {
    printf("\nwrite: %s\n", strerror(errno));
  }
  
  return_val = close(write_fd);
  if (return_val == 1) {
    printf("\nclose: Unsuccessful\n");
  }

  // reads the file into a different array without using a loop

  int read_fd = open("randfile", O_RDONLY);
  if (read_fd == -1) {
    printf("\nread: %s\n", strerror(errno));
  }

  unsigned int rand_array2[10];
  printf("\nReading numbers from file...\n");
  return_val = read(read_fd, rand_array2, sizeof(int) * 10);
  if (return_val == -1) {
    printf("\nread: %s\n", strerror(errno));
  }

  printf("\nVerification that written values were the same:\n");
  for (i = 0; i < 10; i++) {
    printf("\trandom %d: %u\n", i, rand_array2[i]);
  }
  
  return_val = close(read_fd);
  if (return_val == 1) {
    printf("\nclose: Unsuccessful\n");
  }
  
  return 0;
}