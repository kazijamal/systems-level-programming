#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>
#include "headers.h"

int main() {
  
  int size = 256;
  char input[size];
  
  while (strcmp(input, "exit")) {
    
    char username[LOGIN_NAME_MAX];
    getlogin_r(username, LOGIN_NAME_MAX);
    
    char hostname[HOST_NAME_MAX];
    gethostname(hostname, HOST_NAME_MAX);
		  
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));

    
    printf("%s@%s:%s$ ", username, hostname, cwd);
    fgets(input, size, stdin);
    remove_newline(input);
    if (strchr(input, ';') == NULL) {
      run_command(input);
    }
    else {
      run_commands(input, num_args(input, ";"));
    }
    
  }
  
  return 0;
  
}
