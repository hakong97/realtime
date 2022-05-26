#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include "shm.h"
#include <signal.h>

int shmid; //SIGINT 핸들러에서 처리 위해 전역변수로 선언
void* thr_recv (void* data); //메세지를 받는 thread 함수
void* thr_send (void* data); //메세지를 보내는 thread 함수
void sig_int(int signo)
{
	printf("\t End...\n");
	shmctl(shmid, IPC_RMID, NULL); //공유메모리 삭제
	exit(1);
}
int main (void)
{
	void* shmaddr = NULL;
	char buf[1023];

	if((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) == -1) // Shared Memory 식별자 생성
	{
		printf("SHMGET FAILED\n");
		exit(0);
	}

	if((shmaddr = shmat(shmid, NULL, 0)) == (void*)-1) //Shared Memory에 연결
	{
		printf("SHMAT FAILED\n");
		exit(0);
	}
	if(signal(SIGINT, sig_int) == SIG_ERR)
	{
		perror("SIGERR");
		exit(1);
	}
	printf("SHM_id : %d, SHM_Address : %p\n", shmid, shmaddr);
	printf("\t User2 \n");
	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, thr_recv, shmaddr); //thread1 (thr_recv) 생성
	pthread_create(&tid2, NULL, thr_send, shmaddr); //thread2 (thr_send) 생성

	while(1); //반복
}

/*
 * 1 : User1's Message
 * 2 : User2's Message
 * 0 : Empty Memory Space
 */
void* thr_recv(void* data)
{
	void* shm_segment = data;
	while(1)
	{
		if(*((char*)shm_segment) == 1) //첫번째 바이트 값이 '1'이라면
		{
			printf("User1 : %s", (char*)shm_segment+1); //두번째 바이트부터 담긴 문자열 출력
			*(char*)shm_segment = 0; //다시 첫번째 바이트 값을 '0'으로 설정
		}
	}
}

void* thr_send(void* data)
{
	char buf[1023]; //사용자로부터 입력 받을 버퍼
	void* shm_segment = data;
	while(1)
	{
		if(*(char*)shm_segment == 0) //첫번째 바이트 값이 '0' 이라면
		{
			fgets(buf, 1023, stdin); //사용자로부터 입력 받음
			sprintf((char*)shm_segment+1, "%s", buf); //두번째 바이트공간부터 입력 받은 문자열 저장
			*(char*)shm_segment = 2; //다시 첫번째 바이트 값을 '2'로 설정
		}
	}
}
