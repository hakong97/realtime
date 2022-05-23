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

	printf(" ----- (CLIENT) -----\n");
	if(mkfifo("./CtoS_FIFO", 0666) == -1) //CtoS_FIFO 생성
	{
		perror("mkfifo");
		exit(1);
	}
	if((pd_receive = open("./StoC_FIFO", O_RDONLY|O_NONBLOCK)) == -1) // read에서 block되는걸 방지하기 위해 nonblock으로 생성
	{
		perror("open");
		exit(1);
	}

	if((pd_send = open("./CtoS_FIFO", O_WRONLY)) == -1)
	{
		perror("open");
		exit(1);
	}
	/* 쓰레드를 통해 구현하였음. */
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
	pd = *((int*)data); //
	while(1)
	{
		write(1, "To Server : ", 12);
		read(0, msg_send, 64); //보낼 메세지 입력받는다
		n = write(pd, msg_send, strlen(msg_send)+1); //파이프를 통해 전송
		if(n==-1)
		{
			perror("write");
			exit(1);
		}
		memset(msg_send, 0, 64); //버퍼를 지워준다. (엔터입력 시 재전송되는 경우 방지)
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
			write(1, "\nFrom Server : ", 15);
			write(1, msg_receive, n); //받은 메세지 출력
			write(1, "To Server : ", 13);
			continue;
		}
	}
}
