#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

void myShell();


int main()
{
    myShell();
    return 0;
}

void myShell()
{
    std::string input;
   
    while (true)
    {
        std::cout << "Command$: ";
        std::getline(std::cin, input);
        char *argv[10];
        std::istringstream inputStream(input);
        std::string tok;
        //const char *argv[10];
        int i = 0;
        while (inputStream >> tok)
        {

            argv[i] = &tok[0u];
            std::cout << argv[i] << "\n";
            if (tok.compare("quit") == 0)
            {
                //std::cout << tok;
                return;
            }
            //char *cmd = "ls";
            //char *argv[2];
            //argv[0] = cmd;
            //argv[1] = NULL;
            ++i;

        }

        ++i;
        //std::cout << argv[i] << "\n";
        argv[i] = NULL;
        
        pid_t pid;
        int status;

        if (i < 1) {
            fputs("Usage: must supply a command\n", stderr);
            exit(1);
        }

        //puts("Before the exec");
        //printf("%s\n", argv[0]);

        if ((pid = fork()) < 0) {     /* fork a child process           */
            printf("*** ERROR: forking child process failed\n");
            exit(1);
        }

        else if (pid == 0) {
            if (execvp(argv[1], &argv[1]) < 0) {
                perror("exec failed");
                exit(1);
            }
        }
        else {
            while (wait(&status) != pid);
        }

        //puts("After the exec");


    }
}

