#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>
#include "headers.h"

void remove_newline(char * input) {
  int i = 0;
  while (input[i] != '\n') {
    i++;
  }
  input[i] = '\0';
}

int num_args(char * line, char * delimiter) {
  int ans = 0;
  char linecpy[strlen(line)];
  strcpy(linecpy, line);
  char * curr = linecpy;
  while (curr != NULL) {
    strsep(&curr, delimiter);
    ans++;
  }
  return ans;
}

char ** parse_args(char * line, char * delimiter) {
  char ** ans = malloc(sizeof(char*) * (num_args(line, delimiter) + 1));
  char * curr = line;
  int i = 0;
  while (curr != NULL) {
    char * curr_arg = strsep(&curr, delimiter);
    ans[i++] = curr_arg;
  }
  ans[i] = NULL;
  return ans;
}

void fork_exec(char ** args) {
  int cpid = fork();
  if (!cpid) {
    if (execvp(args[0], args) == -1) {
      exit(0);
    }
  }
  else {
    wait(0);
  }
}

void run_command(char * command) {
  char ** args = parse_args(command, " "); 
  if (!strcmp(args[0], "cd")) {
    chdir(args[1]);
  }
  else {
    fork_exec(args);
  }
  free(args);
}

void run_commands(char * line, int num_commands) {
  char ** commands = parse_args(line, ";");
  int i;
  for (i = 0; i < num_commands; i++) {
    run_command(commands[i]);
  }
  free(commands);
}
