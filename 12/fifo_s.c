#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>

void* t_send(void* data);
void* t_receive(void* data);

int main (void)
{
	int pd_send, pd_receive;
	pthread_t tid1, tid2;

	printf("----- (SERVER) -----\n");
	if(mkfifo("./StoC_FIFO", 0666) == -1) //StoC_FIFO 생성
	{
		perror("mkfifo");
		exit(1);
	}
	if((pd_send = open("./StoC_FIFO", O_WRONLY)) == -1)
	{
		perror("open");
		exit(1);
	}

	if((pd_receive = open("./CtoS_FIFO", O_RDONLY|O_NONBLOCK)) == -1) //read시 block 되는것을 방지
	{
		perror("open");
		exit(1);
	}

	/*쓰레드를 통해 구현하였음.*/
	pthread_create(&tid1, NULL, t_send, &pd_send);
	pthread_create(&tid2, NULL, t_receive, &pd_receive);
	
	while(1);
}

void* t_send(void* data)
{
	int pd, n;
	char msg_send[64];
	pd = *((int*)data);
	while(1)
	{
		write(1, "To Client : ", 12);
		read(0, msg_send, 64); //보낼 메세지를 읽는다.
		n = write(pd, msg_send, strlen(msg_send)+1); //메세지를 전송
		if(n == -1)
		{
			perror("write");
			exit(1);
		}
		memset(msg_send, 0, 64); //msg_send 버퍼를 비운다.
	}
}

void* t_receive(void* data)
{
	int pd, n;
	char msg_receive[64];
	pd = *((int*)data);
	while(1)
	{
		if((n=read(pd, msg_receive, 64)) > 0) //받은 메세지를 읽는다.
		{
			write(1, "\nFrom Client : ",15);
			write(1, msg_receive, n); //받은 메세지 출력
			write(1, "To Client : ", 13);
			continue;
		}
	}
}
