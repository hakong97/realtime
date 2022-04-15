#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 64

int main (int argc, char* argv[])
{
	if(argc != 3)
	{
		perror("ARGUMENT ERROR!");
		exit(1);
	}
	char* src_file = argv[1];
	char* dst_file = argv[2];

	int src_fd = open(src_file, O_RDONLY);
	if(src_fd == -1)
	{
		perror("SRC_FILE OPEN ERROR!");
		exit(1);
	}
	int dst_fd = open(dst_file, O_WRONLY|O_CREAT|O_TRUNC, 0644);
	if(dst_fd == -1)
	{
		perror("DST_FILE OPEN ERROR!");
		exit(1);
	}
	int n;
	char buf[BUF_SIZE];

	while((n=read(src_fd, buf, 6))>0)
	{
		if(write(dst_fd, buf, n)!=n)
			perror("WRITE ERROR!");
	}

	if(n==-1)
		perror("READ ERROR!");

	close(src_fd);
	close(dst_fd);
}
