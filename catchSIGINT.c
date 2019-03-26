#include "built-in.h"

/**
	User-defined signal message generator
	Since it is SIGINT -> an int value 2 is expected
*/
static void signalHandler(int signalNum) {
	
	if(signalNum == SIGINT){
		printf("Signal %d - Interactive attention signal caught.\n",signalNum);
		fflush(stdout);
	}else{
		printf("Maybe some other signal you have incidentally caught...");
	}
}

/**
	@brief Function to catch the SIGINT signal once and exit the program
*/
int catchSIGINT(void){
	
	fflush(stdout); // Try commenting out fflush : Nothing changed ?
	
	/*
		C function to handle signal
		[4] SIGINT - Signal Interrupt [Ctrl + C]
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
	
    return 0;
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
