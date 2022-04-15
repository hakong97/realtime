#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[])
{
	if(argc != 3)
	{
		perror("argument");
		exit(1);
	}
	FILE* src_fp;
	FILE* dst_fp;

	if((src_fp = fopen(argv[1], "r")) == NULL)
	{
		perror("FOPEN_SRC");
		exit(1);
	}
	if((dst_fp = fopen(argv[2], "w")) == NULL)
	{
		perror("FOPEN_DST");
		exit(1);
	}
	
	int c;

	while((c = fgetc(src_fp)) != EOF)
	{
		fputc(c, dst_fp);
	}

	fclose(src_fp);
	fclose(dst_fp);


}
