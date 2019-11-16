#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>

int main() {

  DIR * dir = opendir("directory");

  // REQUIREMENTS
  
  
  // list all the files in the directory

  printf("\nListing all the files in the directory\n");

  struct dirent * curr = readdir(dir);

  while (curr != NULL) {
    printf("%s\n", curr->d_name);
    curr = readdir(dir);
  }

  // specify which files are directories (if any)

  printf("\nSpecifying which files are directories\n");

  rewinddir(dir);
  curr = readdir(dir);
  
  while (curr != NULL) {
    if (curr->d_type == DT_DIR) {
      printf("%s\n", curr->d_name);
    }
    curr = readdir(dir);
  }

  // show the total size of all the regular files in the directory

  printf("\nShowing the total size of all the regular files in the directory\n");
  
  rewinddir(dir);
  curr = readdir(dir);
  
  while (curr != NULL) {
    if (curr->d_type == DT_DIR) {
      printf("4096\n");
    }
    else {
      struct stat buffer;
      stat(curr->d_name, &buffer);
      printf("%ld\n", buffer.st_size);
    }
    curr = readdir(dir);
  }

  // have the program scan the current directory

  // POSSIBLE ENHANCEMENTS
  

  // recursively list the files in any subdirectories, update the total to include the total size of subdirectories

  // print out the size in a more readable format (like using KB, MB, GB for -byte prefixes)

  // make it look more like $ ls -l
  
  return 0;
}
