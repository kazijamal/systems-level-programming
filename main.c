#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ** parse_args(char * line) {
  char args[5][256];
  char *curr = line;
  int i = 0;
  while (curr != NULL) {
    printf("[%s]\n", strsep(&curr, " "));
    printf("[%s]\n", curr);
    strcpy(args[i], curr);
  }
}

int main() {
  char line[256] = "ls -a -l";
  parse_args(line);
  return 0;
}
