#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void* t_function(void* data);

int main (int argc, char* argv[])
{
	int state;
	void* t_return;
	pthread_t tid1;
	pthread_t tid2;
	int a = 1;
	int b = 2;
	state = pthread_create(&tid1, NULL, t_function, &a);
	if(state != 0)
	{
		perror("thread1 create error");
		exit(1);
	}
	
	pthread_join(tid1, NULL);

	state = pthread_create(&tid2, NULL, t_function, &b);
	if(state != 0)
	{
		perror("threard2 create error");
		exit(1);
	}
	pthread_join(tid2, NULL);
	puts("main fucntion is end");
	return 0;
}

void* t_function(void* data)
{
	int id;
	int i = 0;
	id = *((int*)data);

	while(1)
	{
		printf("(%lu) %d : %d\n", pthread_self(), id, i);
		i++;
		if(i == 5)
			return (void*)i;
		sleep(1);
	}
}
