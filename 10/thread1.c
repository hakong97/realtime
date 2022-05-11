#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void* thread_function(void* arg);

int main (int argc, char* argv[])
{
	int state;
	void* t_return;
	pthread_t tid;
	state = pthread_create(&tid, NULL, thread_function, argv[1]);

	if(state != 0)
	{
		perror("thread create error");
		exit(1);
	}
	sleep(3);
	state = pthread_join(tid,(void*)&t_return);
	if(state != 0)
	{
		perror("thread join error");
		exit(1);
	}
	puts("main fucntion is end");
	return 0;
}

void* thread_function(void* arg)
{
	printf("%s\n", (char*)arg);
	int i;
	for(i=0;i<3;i++)
	{
		sleep(2);
		puts("Thread is running...");
	}
}
