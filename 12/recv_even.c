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
	int i = 1;

	while(1)
	{
			msgctl(msgid, IPC_STAT, &q_buf); //메세지 큐 정보를 받아온다.
			if(q_buf.msg_qnum > 0) //메세지 큐에 메세지가 1개 이상 있을 시
			{
				len = msgrcv(msgid, &inmsg, 80, 2, 0); //mtype이 짝수인 메세지를 출력한다.
				printf("%d. Received Message : %s, Len : %d\n", i, inmsg.mtext, len);
				i++;
			}
			else
				continue;
	}
}
