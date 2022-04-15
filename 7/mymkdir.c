#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main (int argc, char* argv[])
{
	if(argc != 2)
	{
		perror("argument");
		exit(1);
	}

	if(mkdir(argv[1], 0755) == -1)
	{
		perror("mkdir");
		exit(1);
	}
	return 0;
}
