#include <stdio.h>
#include <stdlib.h>

struct person
{
	char name[10];
	int age;
};

int main (int argc, char* argv[])
{
	struct person d;

	if(argc != 2)
	{
		perror("Argument");
		exit(1);
	}
	
	int n;
	FILE* src;
	src = fopen(argv[1], "r");
	
	printf("Name    Age\n");
	while((n=fread(&d, sizeof(d), 1, src)) > 0)
	{
		printf("%s    %d\n", d.name, d.age);
	}

	fclose(src);
}
