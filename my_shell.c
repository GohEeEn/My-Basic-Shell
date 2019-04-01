// ----- Preprocessor Constant [PROGRAM VERSION DISPLAY] -----
#define PROGRAM_NAME "assign2-17202691"
#define AUTHOR "Ee En Goh"
#define STUDENT_NUMBER 17202691
#define EMAIL "ee.goh@ucdconnect.ie"
#define VERSION 1.0
// ----- End of Preprocessor Constant -----

#include "features.h"
#include "string_operations.h"

// ----- Function Declaration -----

void shell_loop(void);
void startCommand(void);

// ----- End of Function Declaration -----

/**
* @brief Read command given from stdin and execute it repeatedly
*/
void shell_loop(void){

	/** String to store the whole command given */
	char *line;

	/** String array to store the split command input on stdin by white space-character */
	char **args;

	/** The total number of arguments in the stdin string */
 	int num_args = 0;

	startCommand();
	line = read_line();							// Read Command Line 	: SUCCESS
	
	while(line != NULL){	
		
		args = string_split(line,&num_args);	// Split String 		: SUCCESS
		redirect_stdout(&num_args,args);
		
		printf("\n");

		free(line);
		free(args);
		
		startCommand();
		line = read_line();						// Read Command Line 	: SUCCESS
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

/**
 * Shell body function
 */
int main(int argc, char **argv){

	shell_loop();

	return EXIT_SUCCESS;
}
