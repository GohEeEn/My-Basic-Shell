#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

void shell_loop(void);
void startCommand(void);
int change_dir(char **args);
int catchSIGINT(void);
int current_time();
int num_commands_available(void);
int shell_execution(char **args, int redirection_bool);
int shell_lauch(char **argv, int file_descriptor);
int shell_exit(char** argv);
int redirect_stdout(int *num_args, char **args);


