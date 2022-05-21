#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>

void sig_int(int signo)
{
	printf("Chatting Finished!\n");
	exit(1);
}
int main (void)
{
	int pd, n;
	char msg[80];
	
	signal(SIGINT, sig_int);

	if((pd = open("./HAN-FIFO", O_RDONLY)) == -1)
	{
		perror("open");
		exit(1);
	}

	printf(" ----- Client -----\n");
	write(1, "To Server : ", 13);
	scanf("%s", msg);
	while(1)
	{
		n=write(pd, msg, strlen(msg)+1);
		if(n == -1)
		{
			perror("write");
			exit(1);
		}
	}

	close(pd);
}
