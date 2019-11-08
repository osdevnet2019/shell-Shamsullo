#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

void read_command(char *par[], bool isBackground)
{
	char line[1024];
    
    int count = 0;
    for(;;)
    {
        int c =  fgetc(stdin);
        line[count++] = (char) c;
        if (count == '\n') break;

    }
    
    if(count == 1) return;
    char *pch = strtok (line, " \n");
    
    int i = 0;
    while(pch != NULL)
    {
    	if(strcmp(pch, "&") == 0)
    	{
    		isBackground = true;
    	}
        else
        {		
        	par[i++] = pch;
        }
        pch = strtok(NULL, " \n");
    }

    par[i++] = 0;

}

void prompt()
{
    //clearing the screen for the first time
    static bool first_time  = true;
    if(first_time){
        const char* CLEAR_SCREEN_ANSI = " \e[1;1H\e[2J";
        write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
        first_time  = false;
    }

    int u  = getuid();
    //print $ for user and # for root       
    if(u = 0)
    {
        printf("myShell_# ");
    }
    else
    {
        printf("myShell_$ ");
    }
}


int main()
{

    while(1){
		
        prompt();
        
        bool isBackground = false;

        char *par[20];
        read_command(par, &isBackground);
	    
	    if(strcmp(par[0], "exit") == 0){break;}
        
        int pid = fork();
        if(pid < 0)
        {
        	fprintf(stderr, "Fork Failed\n");
        }
        else if (pid > 0 and !isBackground)
        {
        	wait(NULL);
        }
        else if(pid > 0 and isBackground)
        {
        	//send to bg
        }
        else
        {
        	execvp(par[0], par);
       
        }

	}

    return 0;

}
