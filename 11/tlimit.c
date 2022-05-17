#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

void sig_alarm(int signo)
{
	printf("TIME LIMIT! PROCESS END\n");
	kill(0, SIGTERM); //SIGTERM 시그널 전송
	while(wait(NULL) != -1); //Child Process가 종료될 때 까지 대기
	exit(1); // 프로그램 종료
}
int main (int argc, char* argv[])
{
	pid_t pid;
	if(argc != 3)
	{
		printf("Usage : ./tlimit seconds program\n");
		exit(1);
	}
	
	if((pid = fork()) == 0) //Child Process 생성
	{
		char command[BUFSIZ];
		sprintf(command, "./%s",argv[2]); //Child에서 실행할 프로그램 명령줄 생성
		if(execl("/bin/sh", "sh", "-c", command, (char*)NULL) == -1) //프로그램 실행
		{
			perror("execl");
			exit(1);
		}
	}
	else //Parent
	{
		if(signal(SIGALRM, sig_alarm) == SIG_ERR) //SIGALRM에 대한 핸들러 지정
		{
			perror("SIGNAL");
			exit(1);
		}
		alarm(atoi(argv[1])); //alarm 설정
		pause();
	}

}
