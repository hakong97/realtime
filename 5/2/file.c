#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[])
{
	if(argc != 2)
	{
		perror("Argument");
		exit(1);
	}
	struct stat buf;
	lstat(argv[1], &buf);
	printf("Mode = %o (16: %x)\n", (unsigned int)buf.st_mode, (unsigned int)buf.st_mode);
	int kind = buf.st_mode & S_IFMT;
	printf("Kinde = %x\n", kind);

	switch(kind)
	{
		case S_IFDIR:
			printf("%s : Directory\n", argv[1]);
			break;
		case S_IFREG:
			printf("%s : Regular File\n", argv[1]);
			break;
		case S_IFLNK:
			printf("%s : Link File\n", argv[1]);
			break;
	}
	return 0;
}
