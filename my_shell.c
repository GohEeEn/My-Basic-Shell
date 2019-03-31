// ----- Preprocessor Constant [PROGRAM VERSION DISPLAY] -----
#define PROGRAM_NAME "assign2-17202691"
#define AUTHOR "Ee En Goh"
#define STUDENT_NUMBER 17202691
#define EMAIL "ee.goh@ucdconnect.ie"
#define VERSION 1.0
// ----- End of Preprocessor Constant -----

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
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
*/

// ----- Function Declaration -----
int num_commands_available(void);
void shell_loop(void);
char** shell_split(char *command_line);
int shell_exit(char **argv);
char* read_line(void);
int shell_lauch(char **argv);
int shell_execution(char **args);
// ----- End of Function Declaration -----


/**
 * Commands available in the current shell
 */
char *commands_available[] = {
	
	"cd", 	// change directory
	"time", // display the date and local time with the format : [dd/mm hh:mm]# 
	"exit"	// exit this shell
};

int (*command_function[])(char **) = {
	&change_dir,
	&current_time,	// Feature 2
	&shell_exit
};

/**
 * Number of commands availabe in this basic shell
 */
int num_commands_available(){
	return sizeof(commands_available)/sizeof(char *);
}

/**
 * Method to read a line of command input from stdin
 */
char* read_line(void){

	size_t size = 100;
	char *line = malloc(sizeof(char) * size);
	size_t char_length = 0;
	int line_read_successfully = 1;

	if(!line){
		perror("my_shell : ");
		exit(EXIT_FAILURE);
	}

	do{
		catchSIGINT();  // Feature 3 : enable catch SIGINT

		char_length = getline(&line,&size,stdin); // Read the stdin in command line

		// It means the buffer has insufficient memory space to store the input
		if(char_length >= size){

			line_read_successfully = 0 ;
			size *= 2;
			line = realloc(line, size) ; // Enlarge the buffer

			if(!line){
				perror("my_shell : ");
				exit(EXIT_FAILURE);
			}

		}else{
			line_read_successfully = 1;
			return line;
		}

	}while(!line_read_successfully);

	return NULL;
}

/**
 * @brief Function to calculate the character length of the given, including any whitespace character (eg. '\n')
 */
int string_length (char *string){
	int length ;	
	for(length = 0; string[length] != '\0'; ++length);
	return length;
}

/**
 * @brief Function to remove the new line character from the string fetched from stdin
 */
void remove_new_line(char *string){
	
	int command_length = string_length(string);
 
	if(string[command_length - 1] == '\n'){
		string[command_length - 1] = '\0';
	//	printf("After remove new line character : %s\n", string); DEBUG
	}else{
		puts("No new line character to be removed"); // Expected won't happened
	}	
}

/**
 *@brief Split a line of string into each whitespace-separated string
 *@param command_line 	The line of string that got from the standard input
 *@return				Null-terminated string array
 */
char** shell_split(char *command_line){
	
	int bufsize = 64; 					// The size of the string buffer
	int position = 0;
	char **splits = malloc(bufsize * sizeof(char*));	// The string array that will be returned
	char *token;			// The temporary memory space to store the separated string
//	char *string;
	char **splits_backup ;		// The temporary memory space to store the uncompleted string array, when out of space in 'splits' variable

	const char separator[2] = " ";	// Whitespace character, which is the separation token
// 	int i = 0;

	if(!splits){	// Failure in creating an empty space in a memory region
		printf("Enter 3 : Unsuccessful \n");
		perror("my_shell : ");
		exit(EXIT_FAILURE);
	}
	
	// Get the first token 
	remove_new_line(command_line);
	token = strtok(command_line, " \n");

	// Read and do the word-separating process until no string remain
	while(token != NULL){
				
// 		string = strcpy(splits[i++],token); // BUG, further implementation needed to gonna use it
		splits[position++] = token;
			
		// If the current memory space is not sufficient enough to store all the whitespace-separated string
		if(position >= bufsize){

			bufsize *= 2; 						// Set the size of the new buffer into 2 time bigger
			splits_backup = splits;					// Store the successfully-split string into a temporary memory space
			splits = realloc(splits, bufsize * sizeof(char*));	// Enlarge the size of the 2D array

			if(!splits){	// Failure in creating a larger empty space in a memory region
					free(splits_backup);
					perror("my_shell : ");
					exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, separator); // Get the next token from undone spliting of previous string
	}

	splits[position] = '\0'; //TODO

	return splits;
}

/**
*	@brief  The method to exit this program / shell
*	@return Always 0 in order to terminate the program execution
*/
int shell_exit(char** argv){
	return 0;
}

/**
*	@brief			Lauch a program and wait for it to terminate
*	@param	argv	Null-terminated list of arguments from the program
*	@return 		1, in order to continue the execution
*	TODO Feature 1
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
		if(execvp(argv[0], argv) == -1){   // Case if the file not found
			perror("my_shell ");
		}
		exit(0);
		
	}else if(pid < 0){ 	// Case if the creation of child process was unsuccessful
		perror("my_shell ");

	}else{				// Parent process - Wait fot the child-process to finish its execution
		printf("Parent process waiting\n");
		wait(&child_status);
	}
	printf("Parent process exiting\n");
	
	return 1;
}

/**
*	@brief		Execute the program or shell built-in, according to the command given
*	@param args	Null terminated list of arguments
*	@return		1 if the shell should continue running, else 0 if it should terminate
*/
int shell_execution(char **args){
	
	if(args[0] == NULL) // Empty command was given in terminal
		return 1;

	for(size_t i = 0 ; i < num_commands_available(); i++){
		
		// If the given command is found in the commands available in this shell
		if(strcmp(args[0],commands_available[i]) == 0){
			// printf("%s selected\n",commands_available[i]); // Function selected DEBUG
			return (*command_function[i])(args);
		}
	}
	
	return shell_lauch(args);
}

/**
*	@brief Read command given from stdin and execute it repeatedly
*/
void shell_loop(void){

	// String to store the whole command given
	char *line;

	// String array to store the splitted command input on stdin by white space-character
	char **args;

	// The status of child process which is executing the current commmand
	int child_status = false;

	do{

		printf("# "); // Indicated as the start of new command line in my_shell

		line = read_line();		// Read Command Line : SUCCESS
		args = shell_split(line);	// Split String : SUCCESS

/*
		printf("size of args : %ld\n",sizeof(args)/sizeof(args[0]));
		for(int i = 0; i < sizeof(args)/sizeof(args[0]) ; i++){
			printf("%d. %s \n", i, args[i]);
		}
*/		printf("Number of strings in array : %d\n",num_strings(args));

		child_status = shell_execution(args);

		// Free up the memory of string array after the command execution
		free(line);
		free(args);

	}while(child_status);
}

/**
 * @brief Function to calculate the total number of strings in the array
 */
int num_strings(char **argv){

	int string_count = 0;

	printf("Size of array_strings : %ld\n",sizeof(argv)/sizeof(char*)); // Works

	for(size_t i = 0 ; i < sizeof(argv)/sizeof(char*) ; i++){

		size_t j = 0;
		for(j = 0 ; argv[i][j] != '\0' ; j++)
		if(argv[i][j] == '\0')
			string_count++;
		printf("%ld string : %s , reading end\n",i,argv[i]);
	}

	printf("Number of string in this string array : %d\n",string_count);

	return string_count;
}

int checkPipe(char **argv){

	for(size_t i = 0; i <  ;i++){

	}
	return 0;
}

int main(int argc, char **argv){

	// A. Intialize : Read and execute its config files, if any

	// B. Interpret : Read commands from stdin and executes them (in loop)
	shell_loop();

	// C. Terminate : Perform any shutdown/cleanup commands, free up any memory and terminates, after the commands executed
	return EXIT_SUCCESS;
}
