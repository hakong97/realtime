#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// if(execl("/bin/sh", "sh", "-c", command, (char*)NULL) == -1)

int main (int argc, char* argv[])
{
	pid_t pid;
	int status;
	
	char* vt[3];
	vt[0] = "ls";
	vt[1] = "-a";
	vt[2] = NULL;

	if((pid=fork())<0)
	{
		perror("fork");
		exit(1);
	}
	else if(pid == 0) //Child
	{	
		if(execvp("ls", vt) == -1)
		{
			perror("execvp");
			exit(1);
		}
		exit(0);
	}
	else //Parent
	{
		waitpid(pid, &status, 0);
		exit(0);
	}
}
