#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main (int argc, char* argv[])
{
	if(argc != 2)
	{
		perror("Argument Error");
		exit(1);
	}

	int fd = open(argv[1], O_RDONLY);
	if(fd == -1)
	{
		perror("FOPEN_DATA_FILE");
		exit(1);
	}

	char buf[1];
	int read_size;

	while((read_size = read(fd, buf, 1)) > 0) // read character
	{
		if(lseek(fd, 0, SEEK_CUR)%2 == 0)
			continue;
		write(1, buf, 1); //write to stdout
	}

	close(fd);
}

