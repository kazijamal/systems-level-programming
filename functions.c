#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>
#include "headers.h"

char * strip(char * input) {
  while (*input == ' ') {
    input++;
  }
  int i = strlen(input) - 1;
  while (input[i]) {
    if (input[i] == '\n' || input[i] == ' ') {
      input[i] = '\0';
    }
    i++;
  }
  return input;
}

char ** parse_args(char * line, char * delimiter) {
  char ** ans = malloc(256);
  char * curr = line;
  int i = 0;
  while (curr != NULL) {
    char * curr_arg = strsep(&curr, delimiter);
    // if (strcmp(curr_arg, "") == 0) {
    //   continue;
    // }
    ans[i++] = curr_arg;
  }
  ans[i] = NULL;
  return ans;
}

int contains_redirect(char * input) {
  if (strchr(input, '>')) {
    return 1;
  }
  if (strchr(input, '<')) {
    return 1;
  }
  return 0;
}

void fancy_exec(char ** args) {
  if (execvp(args[0], args) == -1) {
    if (strcmp(args[0], "cd")) {
      printf("%s: command not found\n", args[0]);
    }
    free(args);
  }
}

void pipe_func(char * command) {
    char ** commands = parse_args(command, "|");
    char * pipein = strip(commands[0]);
    char * pipeinto = strip(commands[1]);
    char currline[256];
    char input[256];
    FILE *read = popen(pipein, "r");
    while(fgets(currline, 256, read)) {
        currline[sizeof(currline) - 1] = '\0';
        strcat(input, currline);
    }
    pclose(read);
    FILE *write = popen(pipeinto, "w");
    fprintf(write, "%s", input);
    pclose(write);
}

void redirect_stdout(char * command) {
    char ** commands = parse_args(command, ">");
    int writefile = open(strip(commands[1]), O_CREAT | O_WRONLY, 0644);
    dup2(writefile, STDOUT_FILENO);
    char ** args = parse_args(strip(commands[0]), " ");
    fancy_exec(args);
    close(writefile);
}

void redirect_stdin(char * command) {
    char ** commands = parse_args(command, "<");
    int readfile = open(strip(commands[1]), O_RDONLY, 0644);
    dup2(readfile, STDIN_FILENO);
    char ** args = parse_args(strip(commands[0]), " ");
    fancy_exec(args);
    close(readfile);
}

void run_command(char * command) {
  command = strip(command);
  char ** commands = parse_args(command, ";");
  int i;
  for(i=0; commands[i] != NULL; i++) {
    commands[i] = strip(commands[i]);
    if (strchr(commands[i], '|')) {
      pipe_func(commands[i]);
    }
    else {
      char ** args;
      if (!contains_redirect(commands[i])) {
        args = parse_args(commands[i], " ");
        if (!strcmp(args[0], "exit")) {
          free(args);
          exit(0);
        }
        if (!strcmp(args[0], "cd")) {
          chdir(args[1]);
        }
      }

      int childPID = fork();
      if (!childPID) {
        if (strchr(commands[i], '>')) {
          redirect_stdout(commands[i]);
        }
        else if (strchr(commands[i], '<')) {
          redirect_stdin(commands[i]);
        }
        else {
          fancy_exec(args);
          exit(0);
        }
      }
      else {
        wait(0);
      }
    }
    free(commands);
  }
}