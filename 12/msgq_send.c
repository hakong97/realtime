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

	key = ftok("keyfile", 1);
	msgid = msgget(key, IPC_CREAT|0644);
	if(msgid == -1)
	{
		perror("msgget");
		exit(1);
	}
	
	if((atoi(argv[1]) % 2) == 0)
		mesg.mtype = 2;
	else
		mesg.mtype = 1;
	strcpy(mesg.mtext, argv[2]);
	if(msgsnd(msgid, (void*)&mesg, 80, IPC_NOWAIT) == -1)
	{
		perror("msgsnd");
		exit(1);
	}
}
