#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char* argv[])
{
	if(argc != 2)
	{
		perror("argument");
		exit(1);
	}

	DIR* dp;
	struct dirent* dent;
	struct stat stat_buf;
	char path[BUFSIZ];

	if((dp = opendir(argv[1])) == NULL)
	{
		perror("OPENDIR");
		exit(1);
	}

	while((dent = readdir(dp)))
	{
		if(dent->d_name[0] != '.')
		{
			sprintf(path, "%s/%s", argv[1], dent->d_name);
			stat(path, &stat_buf);
			if(S_ISDIR(stat_buf.st_mode))
			{
				printf("NAME : %s\n", dent->d_name);
			}
		}
	}
	closedir(dp);
}
