void remove_newline(char * input);

int num_args(char * line, char * delimiter);

char ** parse_args(char * line, char * delimiter);

void fork_exec(char ** args);

void run_command(char * command);

void run_commands(char * line, int num_commands);
