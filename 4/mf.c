#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>

int main (void)
{
	char buf[1000] = {};

	int fd;
	char* f_name = "size_1";

	fd = open(f_name, O_WRONLY|O_CREAT|O_TRUNC, 0644);
	if(fd == -1)
	{
		perror("FILE OPEN ERROR");
		exit(1);
	}

	while(1)
	{
		if(lseek(fd,0,SEEK_END) == 10000)
			break;
		if(write(fd, buf, 1000) == -1)
			perror("WRITE ERROR");

	}
	close(fd);
}
