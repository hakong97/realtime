#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main (int argc, char* argv[])
{
	if(argc !=2)
	{
		perror("argument error");
		exit(1);
	}
	
	int fd;
	char* file_name = argv[1];
	fd = open(file_name, O_RDONLY);
	if(fd == -1)
	{
		perror("open error");
		exit(1);
	}

	int size = lseek(fd, 0, SEEK_END);
	printf("FILE SIZE = %d Byte\n", size);

	close(fd);
	return 0;
}
