#include <string.h>
#include "features.h"

/**
 * Commands available in the current shell
 */
char *commands_available[] = {
	"cd", 	// change directory
	"exit"	// exit this shell
};

int (*command_function[])(char **) = {
	&change_dir,
	&shell_exit
};

/**
 * Number of commands availabe in this basic shell
 */
int num_commands_available(){
	return sizeof(commands_available)/sizeof(char *);
}

/**
*	@brief  The method to exit this program / shell
*/
int shell_exit(char** argv){
	exit(0);
}

/**
 * @brief Function to do redirection command searching and commands execution
 */
int redirect_stdout(int *num_args, char **args){

	/** String storage that used to store the given filename */
	char *file_name;

	int redirection_bool = 0, file_desc, child_status;

	// Checking if a redirection command given
	for(int i = 0; i < *num_args ; i++){
		
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

	// Case if a redirection command given
	if(redirection_bool){

		file_desc = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666); // Return a new file descriptor
		if(file_desc == -1) { // open() returns -1 upon failure	
			// fprintf(stderr,"Given file %s can't be open or not found\n",file_name);				
			perror("my_shell : "); // Print program detail - success or fail
		}
	}
			
	child_status = shell_execution(args, file_desc); // Execute the given command / program
	redirection_bool = 0;

 	return child_status;
}

/**
*	@brief		Execute the program or shell built-in, according to the command given
*	@param args	Null terminated list of arguments
*	@return		1 if the shell should continue running, else 0 if it should terminate
*/
int shell_execution(char **args, int file_desc){

	// Case 1 : Empty command was given in terminal
	if(args[0] == NULL) 
		return 1;

	// Case 2 : Self-define function called [ie. "cd" & "exit"]
	for(size_t i = 0 ; i < num_commands_available(); i++){
		
		// If the given command is found in the commands available in this shell
		if(strcmp(args[0],commands_available[i]) == 0){
			return (*command_function[i])(args);
		}
	}
	
	// Case 3 : else call built-in command / program
	return shell_lauch(args,file_desc);
}

/**
*	@brief			Lauch a program and wait for it to terminate
*	@param	argv	Null-terminated list of arguments from the program
*	@return 		1, in order to continue the execution
*	Feature 1
*/
int shell_lauch(char **argv, int file_descriptor){

	pid_t pid;
	int child_status;

	pid = fork(); 		// create a child process

	if(pid == 0){ 		// Child process - Execute the given command 
		
		dup2(file_descriptor,1);

		/*
			Execute the command in the given program file name
			args[0] - File name of file which has the content to be executed
			argv 	- Argument list available to the new program provided with its file name 
		*/
		if(execvp(argv[0], argv) == -1){   // Case if the file not found
			fprintf(stderr, "my_shell : Command / program given not found\n");
		}
		
		close(file_descriptor);

		exit(EXIT_SUCCESS);
	
	}else if(pid < 0){ 	// Case if the creation of child process was unsuccessfu
		fprintf(stderr,"my_shell : Child process creation not successful\n");

	}else{				// Parent process - Wait fot the child-process to finish its execution
		wait(&child_status);
	}
	
	return 1;
}
