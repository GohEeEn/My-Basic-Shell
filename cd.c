#include "built-in.h"

int change_dir(char **args){

	char path[100]; // char array to store the name of directory path	

	if(args[1] == NULL) // Case if no argument is given
		fprintf(stderr,"my_shell : expected argument given to command \"cd\"\n");
	else{
		// Case if the change of path is not a success
		if(chdir(args[1]) != 0){
			perror("my_shell");
		}

		// Else print the current working directory
		printf("%s\n",getcwd(path,100));
	}
	return 1;
}