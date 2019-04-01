#include "features.h"

/**
 * @brief Function to do redirection command searching and commands execution
 */
int redirect_stdout(int *num_args, char **args){

	char *file_name;
	int redirection_bool, file_desc;
	int child_status;

	// Checking if a redirection command given
	for(int i = 0; i < num_args ; i++){

		if(redirection_bool){ 		// Next string argument after redirection symbol found
			file_name = args[i]; 	// File Name expected for remaining args
			printf("Given file name : %s\n",file_name);
			args[i-1] = NULL;
			break;
		}

		if(strcmp(args[i],">") != 0){
					redirection_bool = 0;
				}else{
					redirection_bool = 1;
				}
			}

		if(redirection_bool){

			file_desc = open(file_name, O_WRONLY | O_CREAT | O_TRUNC); // Return a new file descriptor

			if(file_desc == -1) { // open() returns -1 upon failure
					// fprintf(stderr,"Given file %s can't be open or not found\n",file_name);
				perror("my_shell : "); // Print program detail - success or fail
			}else{
				printf("File opened or created\n");

				if(chmod(file_name,0644) == -1){ // File Permission change failed
					perror("my_shell : ");
				}
				dup2(file_desc,1);
			}
		}

		child_status = shell_execution(args);

		if(redirection_bool){
			close(file_desc);
			printf("File closed\n");
			redirection_bool = 0;
		}
}
