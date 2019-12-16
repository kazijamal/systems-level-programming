#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>
#include "headers.h"

/*======= char * strip() ===============================
Inputs: char *input
Returns: Pointer to the beginning of input

Removes leading and trailing whitespace from the input
========================================================*/
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

/*======= char ** parse_args() =========================
Inputs: char *line, char *delimiter
Returns: Array of strings where each entry is a token
    separated by a delimiter

If line contains multiple tokens separated by delimiter, 
this function will put each token into an array of strings
========================================================*/
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

/*======= int contains_redirect() ======================
Inputs: char *input
Returns: 0 or 1

If input contains either < or > redirect character, this 
function returns 1, otherwise it returns 0
========================================================*/
int contains_redirect(char * input) {
  if (strchr(input, '>')) {
    return 1;
  }
  if (strchr(input, '<')) {
    return 1;
  }
  return 0;
}

/*======= int contains_double_redirect() ===============
Inputs: char *input
Returns: 0 or 1

If input contains both < and > redirect character, this 
function returns 1, otherwise it returns 0
========================================================*/
int contains_double_redirect(char * input) {
  if (strchr(input, '>')) {
    if (strchr(input, '<')) {
      return 1;
    }
  }
  return 0;
}

/*======= void fancy_exec() ============================
Inputs: char **args

Checks if command is not found, else executes command from 
given arguments
========================================================*/
void fancy_exec(char ** args) {
  if (execvp(args[0], args) == -1) {
    if (strcmp(args[0], "cd")) {
      printf("%s: command not found\n", args[0]);
    }
    free(args);
  }
}

/*======= void pipe_func() =============================
Inputs: char *command
Executes command containing pipe

Uses stdout from first command as stdin for second command
========================================================*/
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

/*======= void redirect_stdout() =======================
Inputs: char *command

Executes command containing stdout redirection
Redirects stdout from command into a newly created and 
written file
========================================================*/
void redirect_stdout(char * command) {
  char ** commands = parse_args(command, ">");
  int writefile = open(strip(commands[1]), O_CREAT | O_WRONLY, 0644);
  dup2(writefile, STDOUT_FILENO);
  char ** args = parse_args(strip(commands[0]), " ");
  fancy_exec(args);
  close(writefile);
}

/*======= void redirect_stdin() ========================
Inputs: char *command

Executes command containing stdin redirection
Redirects stdin into command from read file
========================================================*/
void redirect_stdin(char * command) {
  char ** commands = parse_args(command, "<");
  int readfile = open(strip(commands[1]), O_RDONLY, 0644);
  dup2(readfile, STDIN_FILENO);
  char ** args = parse_args(strip(commands[0]), " ");
  fancy_exec(args);
  close(readfile);
}

/*======= void double_redirect() =======================
Inputs: char *command

Executes command containing both stdout and stdin redirection
========================================================*/
void double_redirect(char * command) {
  char ** readirectIN = parse_args(command, "<");
  char ** readirectOUT = parse_args(strip(readirectIN[1]), ">");

  int readfile = open(strip(readirectOUT[0]), O_RDONLY, 0644);
  dup2(readfile, STDIN_FILENO);
  int writefile = open(strip(readirectOUT[1]), O_CREAT | O_WRONLY, 0644);
  dup2(writefile, STDOUT_FILENO);

  char ** args = parse_args(strip(readirectIN[0]), " ");
  fancy_exec(args);

  close(readfile);
  close(writefile);
}

/*======= void run_command() ===========================
Inputs: char *command

Executes any given command by calling aforementioned 
functions in various conditional statements
========================================================*/
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
        if (contains_double_redirect(commands[i])) {
          double_redirect(commands[i]);
        }
        else if (strchr(commands[i], '<')) {
          redirect_stdin(commands[i]);
        }
        else if (strchr(commands[i], '>')) {
          redirect_stdout(commands[i]);
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
