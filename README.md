# mks65-project1_shell

## KMSH

## by Kazi Jamal and Matthew Chan

### Features:

- Reads a line at a time, parses the line to separate the command from its arguments, and forks and executes the command
- Waits for executed programs to exit before reading the next commands
- Reads and separates multiple line commands on one line with `;`
- Simple redirection using `>` (redirecting stdout) and `<` (redirecting stdin)
- Simple pipes using `|`
- Displays username, hostname, and current working directory on prompt

### Attempted:

- Double redirect

### Bugs:

- Occasionally requires exit command multiple times to exit

### Files & Function Headers:

#### shell.c

- displays username, hostname, and current working directory and gets user input to run as a command

#### functions.c

- handles parsing and executing commands
- `char * strip()`
  - Inputs: char \*input
  - Returns:
- `char ** parse_args()`
  - Inputs: char *line, char *delimiter
  - Returns:
- `int contains_redirect()`
  - Inputs:
  - Returns:
- `void fancy_exec()`
  - Inputs:
  - Returns:
- `void pipe_func()`
  - Inputs:
  - Returns:
- `void redirect_stdout()`
  - Inputs:
  - Returns:
- `void redirect_stdin()`
  - Inputs:
  - Returns:
- `void run_command()`
  - Inputs:
  - Returns:
