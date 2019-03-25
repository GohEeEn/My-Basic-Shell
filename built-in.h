#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // where the function chdir() stored
#include <signal.h>

int change_dir(char **args);
int catchSIGINT(void);