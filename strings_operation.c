#include "string_operations.h"

/**
 * @brief Method to read a line of command input from stdin
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
	}else{
		puts("No new line character to be removed"); // Expected won't happened
	}
}

/**
 *@brief Split a line of string into each whitespace-separated string
 *@param command_line 	The line of string that got from the standard input
 *@return				Null-terminated string array
 */
char** string_split(char *command_line, int *num_strings){

	int bufsize = 512; 									// The size of the string buffer
	int position = 0;
	char **splits = malloc(bufsize * sizeof(char*));	// The string array that will be returned
	char *token;										// The temporary memory space to store the separated string
	char **splits_backup ;								// The temporary memory space to store the uncompleted string array, when out of space in 'splits' variable

	// Case if failure in creating an empty space in a memory region
	if(!splits){
		printf("Enter 3 : Unsuccessful \n");
		perror("my_shell : ");
		exit(EXIT_FAILURE);
	}


	remove_new_line(command_line);		// Remove the newline character from string that fetched from stdin
	token = strtok(command_line, " "); 	// Get the first token

	// Read and do the word-separating process until no string remain
	while(token != NULL){

		splits[position++] = token;

		// If the current memory space is not sufficient enough to store all the whitespace-separated string
		if(position >= bufsize){

			bufsize *= 2; 										// Set the size of the new buffer into 2 time bigger
			splits_backup = splits;								// Store the successfully-split string into a temporary memory space
			splits = realloc(splits, bufsize * sizeof(char*));	// Enlarge the size of the 2D array

			if(!splits){	// Failure in creating a larger empty space in a memory region
				free(splits_backup);
				perror("my_shell : ");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, " "); 	// Get the next token from undone splitting of previous string
	}

	splits[position] = '\0';
	*num_strings = position; // Store the total number of strings in the string array

	return splits;
}
