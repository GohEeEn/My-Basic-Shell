#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // where the function chdir() stored
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>

int change_dir(char **args);
int catchSIGINT(void);
int current_time(void);
