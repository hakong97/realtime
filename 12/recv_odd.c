#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>

struct mymsgbuf
{
	long mtype;
	char mtext[80];
};

int main (void)
{
	struct mymsgbuf inmsg;
	key_t key;
	int msgid, len;
	struct msqid_ds q_buf;

	key = ftok("keyfile", 1);
	if((msgid = msgget(key, 0)) < 0)
	{
		perror("msgget");
		exit(1);
	}
	int i = 1; //순번 출력을 위한 변수 i

	while(1)
	{
			msgctl(msgid, IPC_STAT, &q_buf); //메세지큐의 정보를 받아온다.
			if(q_buf.msg_qnum > 0) //큐에 메세지가 1개 이상일시
			{
				len = msgrcv(msgid, &inmsg, 80, 1, 0); // mtype이 홀수인 메세지 출력
				printf("%d. Received Message : %s, Len : %d\n", i, inmsg.mtext, len);
				i++;
			}
			else
				continue;
	}
}
