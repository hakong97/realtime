#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

void sig_child(int signo) //child의 SIGINT에 대한 핸들링
{
	usleep(10); //출력 타이밍 조절
	printf("Child Process die (%d)\n", (int)getpid());
	exit(1);
}
void sig_parent(int signo) //parent의 SIGINT에 대한 핸들링
{
	while(wait(NULL) != -1); //Child 프로세스가 모두 종료될때까지 wait 반복
	printf("Parent Process die (%d)\n", (int)getpid());
	exit(1);
}
void sig_alarm(int signo) // 3초 지났을 때 SIGALRM에 대한 핸들링
{
	printf("After 3 Seconds... All Process die.......\n");
	kill(0, SIGINT); //프로세스 그룹에 SIGINT 시그널 전송
}
int main(void)
{
	int status;
	for(int i=0; i<3;i++) //3개의 프로세스 생성
	{
		int pid;
		pid = fork();
		if(pid == 0)
		{
			if(signal(SIGINT,sig_child)==SIG_ERR) //SIGINT에 대해 sig_child 등록
			{
				perror("SIGNAL");
				exit(1);
			}
			if(i==2)
			{
				printf("3 Child Process Run...\n");
			}
			pause(); //시그널 발생할때까지 대기
		}
	}
	if(signal(SIGINT,sig_parent) == SIG_ERR) //SIGINT에 대해 sig_paranet 등록
	{
		perror("SIGNAL_PARENT");
		exit(1);
	}
	if(signal(SIGALRM, sig_alarm) == SIG_ERR) //SIGALRM에 대해 sig_alarm 등록
	{
		perror("SIGNAL_ALARM");
		exit(1);
	}
	alarm(3); //3초 뒤 SIGALRM 발생
	pause(); //시그널 발생할 때까지 대기
}
