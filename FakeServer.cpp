#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <pthread.h>
#include <errno.h>
#include <string>
#include <iostream>
//A C program using the termios library to disable echo
//in the terminal - by Pieter Holleman


int dispatch();
void* do_greeting2 (void* arg);
int download(const std::string filename)
{
	std::cout << "File requested: " << filename << "\n";
	return 0;
}

//main function as entry point for program
int main(int argc, char* argv[]) {

	//printf("Hello World");
	dispatch();
	return 0;
}

//Function to disable echo
int dispatch() {

	int count;
	pthread_t thread1;
	int status;
	void* result1;
	std::string input;

	while (true)
	{

		std::cout << "Command$: ";
		std::getline(std::cin, input);

		if (input.compare("quit") == 0) return 0;

		if ((status = pthread_create (&thread1, NULL, do_greeting2, NULL)) != 0)
		{
			std::cerr << "thread create error: " << strerror(status) << std::endl;
			exit (1);
		}
		else 
		{
			count++;
			pthread_detach(thread1);
		}
		// if ((status = pthread_join (thread1, &result1)) != 0)
		// {
		// 	std::cerr << "join error: " << strerror(status) << std::endl;
		// 	exit (1);
		// }

	}



	return 1;

}

void* do_greeting2 (void* arg)
{
	int val = rand() % 2;

	// print out message based on val
	std::cout << "thread" << std::endl;
	return arg;
}


