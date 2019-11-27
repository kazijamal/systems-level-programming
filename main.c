#include <stdio.h>
#include <stdlib.h>
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
