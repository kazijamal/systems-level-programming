#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

char ** parse_args(char * line) {
  char ** ans = malloc(sizeof(char*) * 10);
  char * curr = line;
  int i = 0;
  while (curr != NULL) {
    ans[i++] = strsep(&curr, " ");
  }
  ans[i] = NULL;
  return ans;
}

void remove_newline(char * input) {
  int i = 0;
  while (input[i] != '\n') {
    i++;
  }
  input[i] = '\0';
}

void fork_exec(char ** args) {
  if (fork() == 0) {
    execvp(args[0], args);
  }
  else {
    wait(NULL);
  }
}

void run_command(char * command) {
  char ** args = parse_args(command); 
  if (!strcmp(command, "cd")) {
    chdir(args[1]);
  }
  else {
    fork_exec(args);
  }
}

int main() {
  int size = 256;
  char input[size];
  
  while (strcmp(input, "exit")) {
    char cwd[256];
    getcwd(cwd, sizeof(cwd));
    printf("kmsh:%s$ ", cwd);
    
    fgets(input, size, stdin);
    remove_newline(input);
    run_command(input);
  }
  
  return 0;
}
