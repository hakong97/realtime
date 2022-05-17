#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

void sig_alarm(int signo)
{
	printf("TIME LIMIT! PROCESS END\n");
	kill(0, SIGINT);
}
int main (int argc, char* argv[])
{
	pid_t pid;
	if(argc != 3)
	{
		printf("Usage : ./tlimit seconds program\n");
		exit(1);
	}
	
	if((pid = fork()) == 0) //child
	{
		char command[BUFSIZ];
		sprintf(command, "./%s",argv[2]);
		if(execl("/bin/sh", "sh", "-c", command, (char*)NULL) == -1)
		{
			perror("execl");
			exit(1);
		}
	}
	else
	{
		if(signal(SIGALRM, sig_alarm) == SIG_ERR)
		{
			perror("SIGNAL");
			exit(1);
		}
		alarm(atoi(argv[1]));
		while(wait(NULL) != -1);
	}

}
