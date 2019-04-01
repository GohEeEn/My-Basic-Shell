#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // where the function chdir() stored
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int change_dir(char **args);
int catchSIGINT(void);
int current_time();
int shell_execution(char **args, int redirection_bool);
int shell_lauch(char **argv, int file_descriptor);
int shell_exit(char** argv);
int redirect_stdout(int *num_args, char **args, int *file_descriptor);


