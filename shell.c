#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

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
  int size = 256;
  char input[size];

  while (strcmp(input, "exit")) {
    fgets(input, size, stdin);
    int i = 0;
    while (input[i] != '\n') {
      i++;
    }
    input[i] = '\0';
    char ** args = parse_args(input);
    fork();
    wait();
    execvp(args[0], args);
  }
  
  return 0;
}
