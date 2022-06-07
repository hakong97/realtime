#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "prodcons.h"

int semid; //세마포어id를 전역변수로 설정
/*
 * 0 : mutex
 * 1 : empty
 * 2 : full
 */
int wait(int semnum) //semid 대신 세마포어 넘버를 넘겨받는다
{
	struct sembuf buf;
	buf.sem_num = semnum; 
	buf.sem_op = -1;
	buf.sem_flg = SEM_UNDO;
	if(semop(semid, &buf, 1) == -1)
	{
		perror("wait");
		exit(1);
	}
	return 0;
}

int signal(int semnum) 
{
	struct sembuf buf;
	buf.sem_num = semnum;
	buf.sem_op = 1;
	buf.sem_flg = SEM_UNDO;
	if(semop(semid, &buf, 1) == -1)
	{
		perror("signal");
		exit(1);
	}
	return 0;
}

union senum
{
	int val;
	struct semid_ds* buf;
	unsigned short* array;
};

int main (void)
{
	/*세마포어 변수*/
	int mutex = 0;
	int empty = 1;
	int full = 2;

	/*공유메모리*/
	BoundedBufferType* pBuf;
	int shmid, i, data;

	union senum arg; //semctl을 위한 공용체
	if((semid = semget(123, 3, IPC_CREAT|0666)) == -1) //세마포어 생성
	{
		perror("semget");
		exit(1);
	}
	arg.val = 1; // mutex 세마포어의 초기값
	if(semctl(semid, 0, SETVAL, arg) == -1)
	{
		perror("semctl");
		exit(1);
	}
	arg.val = MAX_BUF; //empty 세마포어의 초기값
	if(semctl(semid, 1, SETVAL, arg) == -1)
	{
		perror("semctl");
		exit(1);
	}
	arg.val = 0; //full 세마포어의 초기값
	if(semctl(semid, 2, SETVAL, arg) == -1)
	{
		perror("semctl");
		exit(1);
	}
	
	/*공유메모리 생성*/
	if((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) < 0)
	{
		perror("shmget");
		exit(1);
	}

	if((pBuf = (BoundedBufferType*)shmat(shmid, 0, 0)) == (void*) -1)
	{
		perror("shmat");
		exit(1);
	}

	srand(0x9999); //rand() seed
	for(i=0;i<NLOOPS;i++)
	{
		if(pBuf->counter == 0)
		{
			printf("Consumer: Buffer empty. Waiting.....\n");
			while(pBuf->counter == 0);
		}
		
		/*wait*/
		wait(full);
		wait(mutex);
		/*consumer*/
		printf("Consumer: Consuming an item....\n");
		data = pBuf->buf[pBuf->out].data;
		pBuf->out = (pBuf->out+1) % MAX_BUF;
		pBuf->counter--;
		/*signal*/
		signal(mutex);
		signal(empty);
		usleep((rand()%100)*10000);
	}

	printf("Consumer : Consumed %d items.....\n", i);
	printf("Consumer : %d items in buffer.....\n", pBuf->counter);
	if(shmctl(shmid, IPC_RMID, 0) < 0)
	{
		perror("shmctl");
		exit(1);
	}

}
