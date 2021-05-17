/*** printenv.c ***/

// Description
//   printenv - print the environment to stdout
// Synopsis
//   printenv
// Build
//   $ gcc -o printenv printenv.c
//
/*
#include <stdio.h>

int main(int argc, char* argv[], char* envp[]) {
  for (int i = 0;; ++i) {
    char* p = envp[i];
    if (p == NULL) break;
    printf("%s\n", p);
  }
  return 0;
}
*/
//fork_time
/*
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int i;
	int a;
	i = 0;
	pid_t pid;
	pid_t pid1;
	pid = fork();
	//pid1 = fork();
	a = pid;
	if(pid)
	{		printf("Fork-Test %d\n",i);
		a = pid1;
	}
	else
		printf("here\n");
	return EXIT_SUCCESS;
}
*/

/*
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[], char* envp[]) 
{	
	char *ar[3];
	ar[0] = argv[0];
	ar[1] = "-n slkfhjdf'pgvkhbhdofjh";
	ar[2] = NULL;
	execve("//bin/echo", ar, envp);
	return 0;
}
*/