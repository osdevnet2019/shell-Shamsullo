#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

void read_command(char cmd[], char *par[])
{
	char line[1024];
	int count = 0, i = 0, j = 0;
	char *array[100], *pch;


	for(;;)
	{
		int c =  fgetc(stdin);
		line[count++] = (char) c;
		if (c == '\n') break;

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

	printf("myShell-#: "); 
}



int main()
{
	char cmd[100], command[100], *parameters[20];

	//invironment variable
	char *envp[] = {(char *) "PATH=/bin", 0};

	while(1){
		prompt();
		read_command(command, parameters); 

		if(fork() != 0) {	//it is the parent
			wait(NULL);  //wait for child
		}else{
			strcpy(cmd, "/bin/");
			strcat(cmd, command);
			execve(cmd, parameters, envp);
		}

		if(strcmp(command, "exit") == 0){break;}	
	}

	return 0;
}

