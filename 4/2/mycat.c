#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char* argv[])
{
	if(argc != 2)
	{
		perror("ARGUMENT");
		exit(1);
	}

	FILE* fp;
	if((fp = fopen(argv[1], "r")) == NULL)
	{
		perror("FOPEN ERR");
		exit(1);
	}

	int num = 1;
	char buf[BUFSIZ];

	while(fgets(buf, BUFSIZ, fp) != NULL)
	{
		buf[strlen(buf)-1] = '\0'; // Del '\n'
		putchar(num+48); //ASCII : 0, 1...
		putchar(32); // SPACE
		puts(buf);
		num++;
	}

	fclose(fp);

}
