char * strip(char * input);

char ** parse_args(char * line, char * delimiter);

int contains_redirect(char * input);

void fancy_exec(char ** args);

void pipe_func(char * command);

void redirect_stdout(char * command);

void redirect_stdin(char * command);

void run_command(char * command);