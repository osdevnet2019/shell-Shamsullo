#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>

void read_command(char cmd[], char *par[])
{
	char line[1024];
	int count = 0, i = 0, j = 0;
	char *array[100], *pch;

	for(;;)
	{
		int c =  fgetc(stdin);
		line[count++] = (char) c;
		if (count == '\n') break;
	
	}
	if(count == 1) return;
	pch = strtok (line, " \n");

	// parsing the line into words
	while(pch != NULL){
		array[i++] = strdup(pch);
		pch = strtok(NULL, " \n");
	}

	strcpy(cmd, array[0]);
	for(int j = 0; j < i; j++){
		par[j] = array[j];
		par[i] =  NULL; 
	}
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
	char cmd[100], command[100], *parameters[20];

	//invironment variable
	char *envp[] = {(char *) "PATH=/bin", 0};

	while(1){
		prompt();
		read_command(command, parameters); 
		
		if(fork() < 0)
		{
			printf("Fork Failed");
		}

		if(fork() != 0) {	//it is the parent
			
			wait(NULL);  //wait for child
			//check if it is a fg job
			//if yes
			//wait for child to end with wait()
		}else{
			//bin is not a right  address
			strcpy(cmd, "/bin/");
			strcat(cmd, command);
			execve(cmd, parameters, envp);
			// to check if the ecex succeed 
			// if no, print an error
		}

		if(strcmp(command, "exit") == 0){break;}	
	}

	return 0;
}

