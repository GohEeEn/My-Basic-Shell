#include "features.h"

/**
	@brief User-defined signal message generator, and since it is SIGINT -> an int value 2 is expected
*/
static void signalHandler(int signalNum) {
	
	if(signalNum == SIGINT){
	
		// Continue as a symbol to accept the next command
		char **args = NULL;
		puts("");
		current_time(args);
		printf("# ");

		fflush(stdout);
	}else{
		printf("Maybe some other signal you have incidentally caught...");
	}
}

/**
	@brief Function to catch the SIGINT signal once and exit the program
*/
int catchSIGINT(void){
	
	fflush(stdout); // Function to clear the output buffer
	
	/*
		C function to handle signal
		[2] SIGINT - Signal Interrupt [Ctrl + C]
		- Only handle the signal once per this function called
	*/
    if (signal(SIGINT, signalHandler) == SIG_ERR) {
        fprintf(stderr, "An error occurred while setting a signal handler.\n");
        return EXIT_FAILURE;
    }
	
	// Testing method - raising SIG macro SIGINT (so it looks like the interrupting signal has been given, but by program itself instead)
    /*
	printf("Raising the interactive attention signal.\n");
	
    if(raise(SIGINT) != 0) {
        fprintf(stderr, "Error raising the signal.\n");
        return EXIT_FAILURE;
    }
    printf("Exiting.\n");
	*/
	
    return 1;
}

// Functionality testing method 
/*
int main(){
	
	catchSIGINT();
	// signal(SIGINT, signalHandler);
	
	while(1) {
      printf("Going to sleep for a second...\n");
      sleep(1); 
   }
   return 0;
}
*/
