#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int i = 0;
void sig_alarm(int signo)
{
	i++;
	printf("Stopwatch : %d\n", i);
}
int main (void)
{
	if(signal(SIGALRM, sig_alarm) == SIG_ERR)
	{
		perror("SIGNAL");
		exit(1);
	}
	while(1)
	{
		alarm(1);
		pause();
	}
}
