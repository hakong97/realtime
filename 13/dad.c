#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int semlock(int semid)
{
	struct sembuf buf;
	buf.sem_num = 0;
	buf.sem_op = -1; //-1연산
 	buf.sem_flg = SEM_UNDO;
	if(semop(semid, &buf, 1) == -1)
	{
		perror("semlock");
		exit(1);
	}
	return 0;
}

int semunlock(int semid)
{
	struct sembuf buf;
	buf.sem_num = 0;
	buf.sem_op = 1; //+1연산
	buf.sem_flg = SEM_UNDO;
	if(semop(semid, &buf, 1) == -1)
	{
		perror("semunlock");
		exit(1);
	}
	return 0;
}

int main (void)
{
	int fd;
	int sem_id;
	sleep(rand()%2+1); //dad가 늦게 와야하니 sleep
	if((sem_id = semget(101, 1, IPC_CREAT|0666)) == -1) //mom과 같은 101로 key 설정
	{
		perror("semget");
		exit(1);
	}
	
	printf("아빠가 집에 왔다.\n");
	semlock(sem_id); // Semaphore --
	printf("아빠가 냉장고를 확인한다.\n");
	fd = open("fridge", O_CREAT|O_RDWR|O_APPEND, 0666);
	if(lseek(fd, 0, SEEK_END) == 0)
	{
		printf("아빠가 우유를 사러 나간다.\n");
		sleep(2);
		write(fd, "milk ", 5);
		printf("아빠가 냉장고에 우유를 넣고 냉장고를 떠난다.\n");
		if(lseek(fd, 0, SEEK_END) > 5)
			printf("우유를 너무 많이 사왔습니다.\n");
	}
	semunlock(sem_id); // Semaphore ++
	semctl(sem_id, 0, IPC_RMID); //세마포어 제거
}
