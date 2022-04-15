#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person
{
	char name[10];
	int age;
};

int main (int argc, char* argv[])
{
	if(argc != 2)
	{
		perror("Argument");
		exit(1);
	}

	FILE* src;
	src = fopen(argv[1], "w");
	if(src == NULL)
	{
		perror("FILE OPEN");
		exit(1);
	}
	
	int num;
	printf("Number?: ");
	scanf("%d", &num);
	
	int age;
	char buf[10];
	for(int i=0; i<num; i++)
	{
		struct person d;
		printf("Name / Age :");
		scanf("%s %d",buf, &age);
		
		strcpy(d.name, buf);
		d.age = age;

		fwrite(&d, sizeof(d), 1, src);
	}
	fclose(src);
}
