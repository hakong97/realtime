#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

void sig_handler(int signo)
{
	printf("Child Process die (%d)\n", (int)getpid());
}
int main(void)
{
	int status;
	void (*hand)(int);
	hand = signal(SIGINT, sig_handler);
	if(hand == SIG_ERR)
	{
		perror("SIGNAL");
		exit(1);
	}

	int pid1 = fork();
	if(pid1 == 0)
	{
		pause();
	}
	int pid2 = fork();
	if(pid2 == 0)
	{
		pause();
	}
	int pid3 = fork();
	if(pid3 == 0)
	{
		pause();
	}
	printf("3 child process run...\n");
	while(wait(&status) != -1)
		continue;
}
