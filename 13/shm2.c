#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include "shm.h"
int main (void)
{
	int shmid;
	char* num;
	void* shmaddr = NULL;
	char buf[1023];

	if((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) == -1)
	{
		printf("SHMGET FAILED\n");
		exit(0);
	}

	if((shmaddr = shmat(shmid, NULL, 0)) == (void*)-1)
	{
		printf("SHMAT FAILED\n");
		exit(0);
	}
	printf("SHM ID : %d\n", shmid);
	printf("SHM Address :%p\n", shmaddr);
	while(1)
	{
		if(*((int*)shmaddr) == 1)
		{
			printf("Server : %s\n", (char*)(shmaddr+1));
			*(int*)shmaddr = 0;
			continue;
		}
		else
		{
			printf(">>");
			gets(buf);
			strcpy((char*)shmaddr+1, buf);
			*(int*)shmaddr = 1;
		}
	}
	
}
