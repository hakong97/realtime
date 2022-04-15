#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int main (int argc, char* argv[])
{
	struct stat buf;

	if(argc != 2)
	{
		perror("Argument");
		exit(1);
	}

	lstat(argv[1], &buf);
	
	printf("Inode = %d\n", (int)buf.st_ino);
	printf("Mode = %o\n", (unsigned int)buf.st_mode);
	printf("Nlink = %o\n", (unsigned int)buf.st_nlink);
	printf("UID = %d\n", (int)buf.st_uid);
	printf("GID = %d\n", (int)buf.st_gid);
	printf("SIZE = %d\n", (int)buf.st_size);
	printf("Atime = %d\n", (int)buf.st_atime);
	printf("Mtime = %d\n", (int)buf.st_mtime);
	printf("Ctime = %d\n", (int)buf.st_ctime);
	printf("Block Size = %d\n", (int)buf.st_blocks);

	return 0;
}
