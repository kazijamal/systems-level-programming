#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
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

int num_args(char * line, char delimiter) {
  int ans = 0;
  int i;
  for (i = 0; line[i] != '\0'; i++) {
    if (line[i] == delimiter) {
      ans++;
    }
  }
  ans += 1;
  return ans;
}

char ** parse_args(char * line, char delimiter) {
  char ** ans = malloc(sizeof(char *) * (num_args(line, delimiter) + 1));
  char * curr = line;
  int i = 0;
  char strdelim[2];
  strdelim[0] = delimiter;
  strdelim[1] = '\0';
  while (curr != NULL) {
    char * curr_arg = strsep(&curr, strdelim);
    if (strcmp(curr_arg, "") == 0) {
      continue;
    }
    ans[i++] = curr_arg;
  }
  ans[i] = NULL;
  return ans;
}

void fork_exec(char ** args) {
  int cpid = fork();
  if (!cpid) {
    if (execvp(args[0], args) == -1) {
      printf("%s: command not found\n", args[0]);
      free(args);
      exit(0);
    }
  }
  else {
    wait(0);
  }
}

void run_command(char * command) {
  char ** args = parse_args(command, ' ');
  if (!strcmp(args[0], "exit")) {
    free(args);
    exit(0);
  }
  if (!strcmp(args[0], "cd")) {
    chdir(args[1]);
  }
  if ((sizeof(args)/sizeof(char *))>1 && !strcmp(args[1], ">")) {
    char ** redirOut = parse_args(command, '>');
    printf("^$&^$&*^(: %s\n", redirOut[2]);
    int fd = open(redirOut[2], O_WRONLY);
    if (fd < 0) {
		  printf("error %d: %s\n", errno, strerror(errno));
	  }
    dup2(fd, 2);
    char ** redirArgs = parse_args(redirOut[0], ' ');
    fork_exec(redirArgs);
  }
  else {
    fork_exec(args);
  }
  free(args);
}

void run_commands(char * line, int num_commands) {
  char ** commands = parse_args(line, ';');
  int i;
  for (i = 0; i < num_commands; i++) {
    run_command(commands[i]);
  }
  free(commands);
}
