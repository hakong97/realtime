#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[])
{
	if(argc != 3)
	{
		perror("Argument Error");
		exit(1);
	}

	FILE* src_fp = fopen(argv[1], "r");
	if(src_fp == NULL)
	{
		perror("FOPEN_SRC");
		exit(1);
	}
	FILE* dst_fp = fopen(argv[2], "w");
	if(dst_fp == NULL)
	{
		perror("FOPEN_DST");
		exit(1);
	}
	
	int n;
	char buf[1];
	while((n=fread(buf, 1, 1, src_fp)) > 0)
	{
		fwrite(buf, 1, 1, dst_fp);
	}

	fclose(src_fp);
	fclose(dst_fp);
}
