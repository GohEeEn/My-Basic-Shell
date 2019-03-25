#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include "features.h"
#include "built-in.h"


/*
	Basic Shell :
	1. Print a prompt (# character) before any commands 
	2. Read in a line from stdin -> getline() function suggested [trim trailing '\n']
	3. A command follwoed by SPACE separated arguments
	4. Execute the command with the given arguments
	5. Wait until command completes
	6. Print the prompt again and accept more commmands
	7. Exit when EOF is received (Ctrl + D) - Terminate condition 1

	Conditions :
	> Use system() for initial testing, then replace with feature 1
	> Add error checks
		- Exit if your shell does something it should not - Terminate condition 2
		- Print error and stay alive if the user make an error (eg. command not found)
	> Submit at least 2 .c source files and 1 header file (.h source files)	

	@author  : Ee En Goh (17202691)
	@version : 1.0
*/

// Commands available in the current shell
char *commands_available[] = {
	
	"cd", 	// change directory
	"time", // display the date and local time with the format : [dd/mm hh:mm]# 
};

int num_commands_available(){
	return sizeof(commands_available)/sizeof(char *);
}

/**
	@brief Read command given from stdin and execute it repeatedly
*/
void shell_loop(void){
	
	// String to store the whole command given 
	char *line;
	
	// String array to store the splitted command input on stdin by white space-character	
	char **args;	
	
	bool status;		
	
	do{
		
		printf("# "); // Indicated as the start of new command line in my_shell
		
		// Get the command given from stdin
		getline(stdin,line); 
		
		args = strtok(line," ");
		
		status = (bool)shell_execution(args);
		
		// Free up the memory of string array after the command execution
		free(args);
		
	}while(status)
}

/**
	@brief  The method to exit this program / shell
	@return Always 0 in order to terminate the program execution 
*/
int shell_exit(){
	return 0;
}

/**
	@brief			Lauch a program and wait for it to terminate
	@param	args	Null-terminated list of arguments from the program
	@return 		1, in order to continue the execution
*/
int shell_lauch(char **argv){

	pid_t pid;
	int child_status;

	pid = fork(); // create a child process

	if(pid == 0){ 		// Child process - Execute the given command 
		
		/*
			Execute the command in the given program file name
			args[0] - File name of file which has the content to be executed
			argv 	- Argument list available to the new program provided with its file name 
		*/
		if(execvp(argv[0],argv) == -1)   // Case if the file not found  
			perror("my_shell ");
		
		exit(0);
		
	}else if(pid < 0){ 	// Case if the creation of child process was unsuccessful
		perror("my_shell ");
	}else{			// Parent process - Wait fot the child-process to finish its execution
		printf("Parent process waiting\n");
		wait(&child_status);
	}
	printf("Parent process exiting\n");
	
	return 1;
}

/**
	@brief		Execute the program or shell built-in, according to the command given
	@param args	Null terminated list of arguments
	@return		1 if the shell should continue running, else 0 if it should terminate
*/
int shell_execution(char **args){
	
	if(args[0] == NULL) // Empty command was given in terminal
		return 1;

	for(size_t i = 0 ; i < num_commands_available(); i++){
		
		// If the given command is found in the commands available in this shell
		if(strcmp(args[0],builtin_str[i]) == 0){
			
		}
	}
	
	return shell_lauch(args);
}

int main(int argc, char **argv){

	// A. Intialize : Read and execute its config files, if any

	// B. Interpret : Read commands from stdin and executes them (in loop)
	shell_loop();

	// C. Terminate : Perform any shutdown/cleanup commands, free up any memory and terminates, after the commands executed
	return EXIT_SUCCESS;
}