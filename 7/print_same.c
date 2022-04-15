#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

int main (int argc, char* argv[])
{
	if(argc != 2)
	{
		perror("argument");
		exit(1);
	}

	DIR* dp;
	struct dirent* dent;

	if((dp = opendir(argv[1])) == NULL)
	{
		perror("OPENDIR");
		exit(1);
	}

	int ino[BUFSIZ];
	int count = 0;
	while((dent = readdir(dp)))
	{
		ino[count] = dent->d_ino;
		count++;
	}

	for(int i=0; i<count;i++)
	{
		for(int j=i+1; j<count;j++)
		{
			if(ino[i] == ino[j])
				printf("Same inode : %d\n", ino[j]);
		}

	}
	closedir(dp);
}
