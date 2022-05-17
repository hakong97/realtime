#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int i = 0;
void sig_alarm(int signo)
{
	i++;
	printf("Stopwatch : %d\n", i); //초 출력
}
void sig_int(int signo)
{
	printf("Stop : %d\n", i); //중단했을 때 초 출력
	exit(1); //프로그램 종료
}
int main (void)
{
	if(signal(SIGALRM, sig_alarm) == SIG_ERR)
	{
		perror("SIGNAL_ALRM");
		exit(1);
	}
	if(signal(SIGINT, sig_int) == SIG_ERR) // Ctrl+C를 통해 스탑워치 중단
	{
		perror("SIGNAL_INT");
		exit(1);
	}
	while(1)
	{
		alarm(1); // 1초 간격으로 alarm()
		pause(); 
	}
}
