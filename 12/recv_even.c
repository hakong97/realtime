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
			msgctl(msgid, IPC_STAT, &q_buf);
			if(q_buf.msg_qnum > 0)
			{
				len = msgrcv(msgid, &inmsg, 80, 2, 0);
				printf("%d. Received Message : %s, Len : %d\n", i, inmsg.mtext, len);
				i++;
			}
			else
				continue;
	}
}
