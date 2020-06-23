# mks65-project1_shell

## KMSH

## by Kazi Jamal and Matthew Chan

### Features:

- Reads a line at a time, parses the line to separate the command from its arguments, and forks and executes the command
- Waits for executed programs to exit before reading the next commands
- Reads and separates multiple line commands on one line with `;`
- Simple redirection using `>` (redirecting stdout) and `<` (redirecting stdin)
- Double redirection
- Simple pipes using `|`
- Displays username, hostname, and current working directory on prompt

### Attempted But Unsuccessful:

- N/A

### Bugs:

- Occasionally requires exit command multiple times to exit
- When redirecting test commmands as stdin to the shell program, the prompt with username, hostname, and current working directory is displayed multiple times

### Files & Function Headers:

#### shell.c

- displays username, hostname, and current working directory and gets user input to run as a command

#### functions.c

- handles parsing and executing commands
- `char * strip()`
  - Inputs: char \*input
  - Returns: Pointer to the beginning of input
  - Removes leading and trailing whitespace from the input
- `char ** parse_args()`
  - Inputs: char \*line, char \*delimiter
  - Returns: Array of strings where each entry is a token separated by a delimiter
  - If line contains multiple tokens separated by delimiter, this function will put each token into an array of strings
- `int contains_redirect()`
  - Inputs: char \*input
  - Returns: 0 or 1
  - If input contains either < or > redirect character, this function returns 1, otherwise it returns 0
- `int contains_double_redirect()`
  - Inputs: char \*input
  - Returns: 0 or 1
  - If input contains both < and > redirect character, this function returns 1, otherwise it returns 0
- `void fancy_exec()`
  - Inputs: char \*\*args
  - Checks if command is not found, else executes command from given arguments
- `void pipe_func()`
  - Inputs: char \*command
  - Executes command containing pipe
  - Uses stdout from first command as stdin for second command
- `void redirect_stdout()`
  - Inputs: char \*command
  - Executes command containing stdout redirection
  - Redirects stdout from command into a newly created and written file
- `void redirect_stdin()`
  - Inputs: char \*command
  - Executes command containing stdin redirection
  - Redirects stdin into command from read file
- `void double_redirect()`
  - Inputs: char \*command
  - Executes command containing both stdout and stdin redirection
- `void run_command()`
  - Inputs: char \*command
  - Executes any given command by calling aforementioned functions in various conditional statements
