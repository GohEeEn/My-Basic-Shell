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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "features.h"

// ----- Function Declaration -----

int num_commands_available(void);
void shell_loop(void);
char** shell_split(char *command_line, int *num_strings);
void startCommand(void);
char* read_line(void);

// ----- End of Function Declaration -----

/**
 * Method to read a line of command input from stdin
 */
char* read_line(void){

	size_t size = 512;
	char *line = malloc(sizeof(char) * size);
	size_t char_length = 0;
	int line_read_successfully = 1;

	if(!line){
		printf("Error 1");
		perror("my_shell ");
		exit(EXIT_FAILURE);
	}

	do{
		char_length = getline(&line,&size,stdin); // Read the stdin in command line
		
		// Case for Ctrl + D : EOF == Exit Program
		if(feof(stdin)){
			puts("\n");
			exit(0);	
		}

		// It means the buffer has insufficient memory space to store the input
		if(char_length >= size){

			line_read_successfully = 0 ;
			size *= 2;
			line = realloc(line, size) ; // Enlarge the buffer

			if(!line){
				printf("Error 2");
				perror("my_shell ");
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
 * @brief Function to remove the new line character from the string fetched from stdin
 */
void remove_new_line(char *string){
	
	int command_length = strlen(string);
 
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
char** shell_split(char *command_line, int *num_strings){
	
	int bufsize = 512; 					// The size of the string buffer
	int position = 0;
	char **splits = malloc(bufsize * sizeof(char*));	// The string array that will be returned
	char *token;			// The temporary memory space to store the separated string
	char **splits_backup ;		// The temporary memory space to store the uncompleted string array, when out of space in 'splits' variable

	const char separator[2] = " ";	// Whitespace character, which is the separation token

	if(!splits){	// Failure in creating an empty space in a memory region
		printf("Enter 3 : Unsuccessful \n");
		perror("my_shell : ");
		exit(EXIT_FAILURE);
	}
	
	// Get the first token 
	remove_new_line(command_line);
	token = strtok(command_line, " ");

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

	splits[position] = '\0';
	*num_strings = position;
	
	return splits;
}

/**
* @brief Read command given from stdin and execute it repeatedly
*/
void shell_loop(void){

	// String to store the whole command given
	char *line;

	// String array to store the splitted command input on stdin by white space-character
	char **args;

 	int num_args = 0;

	// The status of child process which is executing the current commmand
	int file_descriptor = false;

	startCommand();
	line = read_line();			// Read Command Line 	: SUCCESS
	
	while(line != NULL){	
		
		args = shell_split(line,&num_args);	// Split String 	: SUCCESS
		redirect_stdout(&num_args,args,&file_descriptor);				
		
		printf("\n");
		// Free up the memory of string array after the command execution
		free(line);
		free(args);
		
		startCommand();
		line = read_line();			// Read Command Line 	: SUCCESS
	}
}

/**
* @brief Method to illustrate the start of commands in shell
*/
void startCommand(void){
	
	catchSIGINT();  	// Feature 3 : enable catch SIGINT		
	current_time();		// Feature 2 : Print the current time
	printf("# "); 		// Indicated as the start of new command line in my_shell
}

int main(int argc, char **argv){

	shell_loop();

	return EXIT_SUCCESS;
}
