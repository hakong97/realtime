#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[])
{
	if(argc != 2)
	{
		perror("Argument Error");
		exit(1);
	}

	FILE* rfp = fopen(argv[1], "r");
	if(rfp == NULL)
	{
		perror("FOPEN_DATA_FILE");
		exit(1);
	}
	

	char buf[1];
	int read_size;
	int offset = 0;

	while((read_size = fread(buf, 1, 1, rfp)) > 0)
	{
		fseek(rfp, offset+1, SEEK_CUR);
		fwrite(buf, 1, 1, stdout);
	}
	
	fclose(rfp);
}
