#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (void)
{
	int pd_send, pd_receive, n;
	char msg_send[64];
	char msg_receive[64];

	printf("----- FULL DUPLEX COMMUNICATION (SERVER) -----\n");
	if(mkfifo("./StoC_FIFO", 0666) == -1)
	{
		perror("mkfifo");
		exit(1);
	}
	if((pd_send = open("./StoC_FIFO", O_WRONLY)) == -1)
	{
		perror("open");
		exit(1);
	}

	if((pd_receive = open("./CtoS_FIFO", O_RDONLY|O_NONBLOCK)) == -1)
	{
		perror("open");
		exit(1);
	}

	while(1)
	{
		if((n=read(pd_receive, msg_receive, 64)) > 0)
		{
			printf("\nFrom Client : ");
			write(1, msg_receive, n);
			continue;
		}
		else
		{
			printf("\nTo Client : ");
			scanf("%s", msg_send);
			n = write(pd_send, msg_send, strlen(msg_send)+1);
			if(n == -1)
			{
				perror("write");
				exit(1);
			}
		}
	}
	close(pd_send);
	close(pd_receive);
}
