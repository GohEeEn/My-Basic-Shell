#include "features.h"

/**
	@brief	Function to output the current time in format [date/month hour:minute]
*/
void current_time(){

    char current_time_str[20];
    time_t current = time(0);
    strftime(current_time_str, 20 ,"[%d/%m %H:%M]#", localtime(&current));
    printf("%s\n", current_time_str);
}

// Testing
int main(){
	
	current_time();
	return 0;
}
