#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

void sig_child(int signo)
{
	usleep(10);
	printf("Child Process die (%d)\n", (int)getpid());
	exit(1);
}
void sig_parent(int signo)
{
	while(wait(NULL) != -1);
	printf("Parent Process die (%d)\n", (int)getpid());
	exit(1);
}
void sig_alarm(int signo)
{
	printf("After 3 Seconds... All Process die.......\n");
	kill(0, SIGINT);
}
int main(void)
{
	int status;
	for(int i=0; i<3;i++)
	{
		int pid;
		pid = fork();
		if(pid == 0)
		{
			if(signal(SIGINT,sig_child)==SIG_ERR)
			{
				perror("SIGNAL");
				exit(1);
			}
			if(i==2)
			{
				printf("3 Child Process Run...\n");
			}
			pause();
		}
	}
	if(signal(SIGINT,sig_parent) == SIG_ERR)
	{
		perror("SIGNAL_PARENT");
		exit(1);
	}
	if(signal(SIGALRM, sig_alarm) == SIG_ERR)
	{
		perror("SIGNAL_ALARM");
		exit(1);
	}
	alarm(3);
	pause();
}
