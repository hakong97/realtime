#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>

void* t_send(void* data);
void* t_receive(void* data);

int main (void)
{
	int pd_send, pd_receive;
	pthread_t tid1, tid2;

	printf(" ----- FULL DUPLEX COMMUNICATION (CLIENT) -----\n");
	if(mkfifo("./CtoS_FIFO", 0666) == -1)
	{
		perror("mkfifo");
		exit(1);
	}
	if((pd_receive = open("./StoC_FIFO", O_RDONLY|O_NONBLOCK)) == -1)
	{
		perror("open");
		exit(1);
	}

	if((pd_send = open("./CtoS_FIFO", O_WRONLY)) == -1)
	{
		perror("open");
		exit(1);
	}

	pthread_create(&tid1, NULL, t_send, &pd_send);
	pthread_create(&tid2, NULL, t_receive, &pd_receive);
	while(1);

	
	close(pd_send);
	close(pd_receive);
}

void* t_send(void* data)
{
	int pd, n;
	char msg_send[64];
	pd = *((int*)data);
	while(1)
	{
		write(1, "To Server : ", 12);
		read(0, msg_send, 64);
		n = write(pd, msg_send, strlen(msg_send)+1);
		if(n==-1)
		{
			perror("write");
			exit(1);
		}
		memset(msg_send, 0, 64);
	}
}

void* t_receive(void* data)
{
	int pd, n;
	char msg_receive[64];
	pd = *((int*)data);
	while(1)
	{
		if((n=read(pd, msg_receive, 64)) > 0)
		{
			write(1, "\nFrom Server : ", 15);
			write(1, msg_receive, n);
			write(1, "To Server : ", 13);
			continue;
		}
	}
}
