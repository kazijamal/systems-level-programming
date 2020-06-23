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
  
  while (1) {
    
    char username[LOGIN_NAME_MAX];
    getlogin_r(username, LOGIN_NAME_MAX);
    
    char hostname[HOST_NAME_MAX];
    gethostname(hostname, HOST_NAME_MAX);

    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));

    
    printf("%s@%s:%s$ ", username, hostname, cwd);
    fgets(input, size, stdin);
    
    run_command(input);
  }
  
  return 0;
}
