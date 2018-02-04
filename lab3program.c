#include <signal.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>

//A program to demonstrate interprocess communication using signals
//by Pieter Holleman and Christian Yap
void sigusr1_handler(int);
void sigusr2_handler(int);
void exit_handler(int);

pid_t cpid = 0;


//SIGUSR1 handler
void sigusr1_handler(int signum)
{
	printf("%s\n", "recieved a SIGUSR1 signal");
	
}

//SIGUSR2 handler
void sigusr2_handler(int signum)
{
	printf("%s\n", "recieved a SIGUSR2 signal");
	
}

//exit handler
void exit_handler(int signum)
{
	//instruct child process to gracefull exit
	if (cpid != 0)
	{	
		printf("Time for %d to gracefully exit, and kill %d.\n", getpid(), cpid);
		kill(cpid, SIGTERM);
		exit(0);
	}
	//gracefully exit if child process
	else 
	{
		printf("Time for %d to gracefully exit.\n", getpid());
	}
	exit(0);
}
int main()
{

	//seed random number generator
	srand(time(NULL));
	
	
	pid_t ppid = getpid();
	pid_t who = fork();
	cpid = who;
	
	while (1)
	{
		//reinstall signal handlers after signal 
		signal(SIGINT, exit_handler);
		signal(SIGUSR1, sigusr1_handler);
		signal(SIGUSR2, sigusr2_handler);
		
		//parent process waits for signal
		if (who != 0){
		
		printf("parent: %d waiting... ", getpid());
		pause();	
		
		}
		//child process sends random signal
		else {
		
		//generate random wait time
		int waittime = (rand() % 4) + 2;
	
		//wait
	    sleep(waittime);
	    //randomly select which signal to send
	    int select = rand() % 2;
	    
	    //printf("%d", select); 
	    	switch (select)
	    	{
	    		case 0:
	    			kill(ppid, SIGUSR1);
	    			signal(SIGUSR1, sigusr1_handler);

	    			break;
	    		case 1:
	    			kill(ppid, SIGUSR2);
	    			signal(SIGUSR2, sigusr2_handler);	
	    			break;
	    		default:
	    			printf("%s\n", "fail");
	    			exit(0);
	    	}
		
	}

	

	}
}


// 	if (who == 0){
// 		//close(fd[1]);
// 		int i = 0;
// 		while (1)
// 		{
// 		//printf("process %d waiting... ", getpid());
// 		signal(SIGTERM, exit_handler);
// 		int waittime = rand() % 5;
// 		//printf("child: %d, going to signal %d in %d seconds. ", getpid(), ppid, waittime);
// 	    sleep(waittime);
// 	    int select = rand() % 2;
	    
	    
// 	    	switch (select)
// 	    	{
// 	    		case 0:
// 	    			kill(ppid, SIGUSR1);
// 	    			signal(SIGUSR1, sigusr1_handler);

// 	    			break;
// 	    		case 1:
// 	    			kill(ppid, SIGUSR2);
// 	    			signal(SIGUSR2, sigusr2_handler);	
// 	    			break;
// 	    		default:
// 	    			printf("%s\n", "fail");
// 	    			exit(0);
// 	    	}

// 	    // if (read(fd[0], &c, 1))
// 	    // {	
// 	    // 	printf("%c\n", c);
// 	    // 	exit(0);
// 	    //}

// 		++i;
// 		}
// 	}

// 	else{
// 		//close(fd[0]);
// 		//write(fd[1], 'a', 2);

		
// 		sleep(10);
// 		//printf("parent: %d waiting... ", getpid());
// 		//kill(who, SIGTERM);
// 		pause();	
		
// 	}
	
// 	return 0;



// }