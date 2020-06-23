#include <stdio.h>
#include <stdlib.h>
<<<<<<< HEAD
#include <time.h>
#include "header.h"

int main() {
  srand(time(NULL));

  struct phone newPhone;

  printf("These are five examples of a phone struct, generated with the examplePhone() function and printed with the printPhone() function:\n");
  int i;
  for (i = 1; i <= 6; i++){
    newPhone = examplePhone();
    printPhone(newPhone);
  }

  printf("\n");

  printf("This is the phone that will be modified by the modifyPhone() function:\n");
  struct phone modPhone = examplePhone();
  printPhone(modPhone);
  struct phone *p = &modPhone;
  printf("\nThis is the phone after being modified by the modifyPhone() function:\n");
  modifyPhone(p, "Pear", 9999);
  printPhone(modPhone);
  
  return 0;
}
  
=======
#include <string.h>
#include <unistd.h>

char ** parse_args(char * line) {
  char ** ans = malloc(sizeof(char*) * 6);
  char * curr = line;
  int i = 0;
  while (curr != NULL) {
    ans[i++] = strsep(&curr, " ");
  }
  ans[i] = NULL;
  return ans;
}

int main() {
  char line[256] = "ls -a -l";
  printf("Running: %s\n", line);
  char ** args = parse_args(line);
  execvp(args[0], args);
  return 0;
}
>>>>>>> parseargs/master
