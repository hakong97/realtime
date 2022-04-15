#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main (int argc, char* argv[])
{
	if(argc != 2)
	{
		perror("argument");
		exit(1);
	}

	int src_fd = open(argv[1], O_RDONLY);
	if(src_fd == -1)
	{
		perror("src open");
		exit(1);
	}

	int split_1 = open("Split_01", O_WRONLY|O_CREAT|O_TRUNC, 0644);
	if(split_1 == -1)
	{
		perror("split_01 open");
		exit(1);
	}
	int split_2 = open("Split_02", O_WRONLY|O_CREAT|O_TRUNC, 0644);
	if(split_2 == -1)
	{
		perror("split_02 open");
		exit(1);
	}

	int end_offset = lseek(src_fd, 0, SEEK_END);
	printf("Size : %d\n", end_offset);
	lseek(src_fd, 0, SEEK_SET);
	char buf[10];
	int n;

	while((n=read(src_fd, buf, 1)) > 0)
	{
		if(n == -1)
			perror("Read");
		if(write(split_1, buf, n) != n)
			perror("Write Error_01");
		if(lseek(src_fd, 0, SEEK_CUR) == (int)(end_offset/2))
			break;
	}
	
	while((n=read(src_fd, buf, 1)) > 0)
	{
		if(write(split_2, buf, n) != n)
			perror("Write Error_02");
	}
	close(src_fd);
	close(split_1);
	close(split_2);
}
