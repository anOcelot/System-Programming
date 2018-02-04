#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <ctype.h>

//A C program using the termios library to disable echo
//in the terminal - by Pieter Holleman


int disable_echo();

//main function as entry point for program
int main() {
	
	//printf("Hello World");
	disable_echo();
	return 0;
}

//Function to disable echo
int disable_echo(){

	//beffer to store up to one kilobyte
	char buffer[1000];

	//termios struct to hold the settings with echo disabled
	struct termios disabled_echo_settings;

	//termio struct to save the original settings
	struct termios original_settings;

	//save original settings to both structs
	tcgetattr(STDIN_FILENO, &original_settings);
	tcgetattr(STDIN_FILENO, &disabled_echo_settings);

	//disable echo on the right struct
	disabled_echo_settings.c_lflag &= ~ECHO;

	//load termios settings with echo disabled  
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &disabled_echo_settings);
	fflush(stdout);

	printf("%s\n", "Disabling echo");
	printf("%s\n\n", "Enter your passphrase");
	//get up to one kb of input
	fgets(buffer, 1000, stdin);
    
    //show user what they entered
    printf("You entered: %s\n", buffer);

    //restore original settings and notify user
	tcsetattr(STDIN_FILENO, TCSANOW, &original_settings);	
	printf("%s\n", "Default behavior restored");

	return 1;

}


