#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main (int argc, char* argv[])
{
	if(argc < 3 || argc > 4 )
	{
		perror("MYLN ARGUMENT");
		exit(1);
	}

	struct stat buf;
	if(argc == 3) //Hard link
	{
		lstat(argv[1], &buf);
		printf("Original File i-node : %d\n", (int)buf.st_ino);
		printf("Before Link Count : %d\n", (unsigned)buf.st_nlink);
		if(link(argv[1], argv[2]) == -1)
		{
			perror("make link err");
			exit(1);
		}
		lstat(argv[2], &buf);
		printf("Link File i-node : %d\n", (int)buf.st_ino);
		printf("After Link Count : %d\n", (unsigned)buf.st_nlink);
		
	}

	if(argc == 4) //Symbolic link
	{
		if(strcmp(argv[1], "-s") != 0)
		{
			perror("-s argument err");
			exit(1);
		}
		lstat(argv[2], &buf);
		printf("Original File i-node : %d\n", (int)buf.st_ino);
		printf("Before Link Count : %d\n", (unsigned)buf.st_nlink);
		if(symlink(argv[2], argv[3]) == -1)
		{
			perror("make symlink err");
			exit(1);
		}
		lstat(argv[3], &buf);
		printf("Link File i-node : %d\n", (int)buf.st_ino);
		printf("Symlink File Link Count : %d\n", (unsigned)buf.st_nlink);
	}

	return 0;
}
