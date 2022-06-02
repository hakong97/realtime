#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int semlock(int semid) //Semaphore Lock
{
	struct sembuf buf;
	buf.sem_num = 0;
	buf.sem_op = -1; // -1 연산
	buf.sem_flg = SEM_UNDO;
	if(semop(semid, &buf, 1) == -1)
	{
		perror("semlock");
		exit(1);
	}
	return 0;
}

int semunlock(int semid) //Semaphore Unlock
{
	struct sembuf buf;
	buf.sem_num = 0;
	buf.sem_op = 1; // +1연산
	buf.sem_flg = SEM_UNDO;
	if(semop(semid, &buf, 1) == -1)
	{
		perror("semunlock");
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
	int fd;
	int sem_id;
	union senum arg;
	if((sem_id = semget(101,1, IPC_CREAT|0666)) == -1) // 101로 key 설정, 최대 1만큼 사용가능
	{
		perror("semget");
		exit(1);
	}
	arg.val = 1; //세마포어 값을 1로
	if(semctl(sem_id, 0, SETVAL, arg) == -1) //semctl을 통해 값 설정
	{
		perror("semctl");
		exit(1);
	}
	printf("엄마가 집에 왔다.\n");
	printf("엄마가 냉장고를 확인한다.\n");
	semlock(sem_id); // Semaphore --
	fd = open("fridge", O_CREAT|O_RDWR|O_APPEND, 0666);
	if(lseek(fd, 0, SEEK_END) == 0) //파일에 내용이 없으면
	{
		printf("엄마가 우유를 사러 나간다.\n");
		sleep(3);
		write(fd, "milk ", 5); //파일에 'milk '출력
		printf("엄마가 냉장고에 우유를 넣고 냉장고에서 떠난다.\n");

		if(lseek(fd, 0, SEEK_END) > 5) //파일에 한번이상 출력이 되어있으면
			printf("우유를 너무 많이 사왔습니다.\n");
	}
	semunlock(sem_id); // Semaphore ++
}
