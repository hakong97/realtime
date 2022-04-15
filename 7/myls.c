#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[]) // ./myls .
{
	DIR* dp;
	struct dirent* dent; //d_ino, d_name[]
	struct stat stat_buf;
	char path[BUFSIZ];

	if(argc != 2)
	{
		perror("argument");
		exit(1);
	}

	if((dp = opendir(argv[1])) == NULL)
	{
		perror("OPENDIR");
		exit(1);
	}

	while((dent = readdir(dp))) //read dir_file list from dp
	{
		if(dent->d_name[0] != '.') 
		{
			sprintf(path, "%s/%s", argv[1],dent->d_name);
			stat(path, &stat_buf);

			printf("Name : %s\n", dent->d_name);
			printf("Inode : %d\n", (int)stat_buf.st_ino);
			printf("Mode : %o\n", (unsigned int)stat_buf.st_mode);
			printf("UID : %d\n", (int)stat_buf.st_uid);
			printf("SIZE : %d\n", (int)stat_buf.st_size);
			printf(" - - - - - - - - - - - - - - - - \n");
		}
	}
	closedir(dp);
}
