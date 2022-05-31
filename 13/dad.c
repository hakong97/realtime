#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main (void)
{
	int fd;
	printf("아빠가 집에 왔다.\n");
	sleep(rand()%2+1);
	printf("아빠가 냉장고를 확인한다.\n");

	fd = open("fridge", O_CREAT|O_RDWR|O_APPEND, 0666);
	if(lseek(fd, 0, SEEK_END) == 0)
	{
		printf("아빠가 우유를 사러 나간다.\n");
		sleep(2);
		write(fd, "milk ", 5);
		printf("아빠가 냉장고에 우유를 넣는다.\n");
	}
	if(lseek(fd, 0, SEEK_END)>5)
		printf("(아빠)우유가 이미 존재합니다!\n");
}
