#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>

struct mymsgbuf 
{
	long mtype;
	char mtext[80];
};

int main (int argc, char* argv[])
{

	if(argc != 3)
	{
		printf("Usage : ./msgq_send mtype Message");
		exit(1);
	}
	key_t key;
	int msgid;
	struct mymsgbuf mesg;

	key = ftok("keyfile", 1); //key 생성
	msgid = msgget(key, IPC_CREAT|0644); //메세지 큐 식별자 생성
	if(msgid == -1)
	{
		perror("msgget");
		exit(1);
	}
	
	if((atoi(argv[1]) % 2) == 0) // 입력받은 mtype을 2로 나눠서 나머지가 0일시 (짝수) 
		mesg.mtype = 2; // mtype을 2로 설정한다.
	else
		mesg.mtype = 1; // 나머지가 1인경우 (홀수) mtype을 1로 설정한다.
	strcpy(mesg.mtext, argv[2]); //입력받은 메세지를 msgbuf 구조체에 복사
	if(msgsnd(msgid, (void*)&mesg, 80, IPC_NOWAIT) == -1) //메세지큐 전송
	{
		perror("msgsnd");
		exit(1);
	}
}
