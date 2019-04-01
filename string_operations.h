#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* read_line(void);
void remove_new_line(char *string);
char** string_split(char *command_line, int *num_strings);
