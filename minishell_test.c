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
/*
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[], char* envp[]) 
{
	char *path;

	path = getenv("PATH");
	printf("%s\n", path);
	return (0);
}
*/

//проверить проги с сигрналами 

/*
#include <signal.h>
#include <stdio.h>
 
static wait = 1;
 
void listener(int sig)
{
    //очищаем буфер
    while (getchar() != '\n');
    printf("listener: stop");
    wait = 0;
    _getch();
}
 
void main()
{
    signal(SIGINT, listener);
 
    do {
        //...
    } while (wait);
    _getch();
}
*/
/*
#include <signal.h>
#include <conio.h>
#include <stdio.h>
 
void main() {
    signal(SIGINT, SIG_IGN);
 
    do {
        printf("*");
    } while (1);
 
    _getch();
}
*/
/*
#include<stdio.h>
#include<signal.h>

void handle_sigint(int sig)
{

    printf("Caught signal %d\n", sig);

}

int main()
{

    signal(SIGINT, handle_sigint);

    while (1) ;

    return 0;
}
*/
/*
https://habr.com/ru/post/141206/
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
*/
/*
https://www.opennet.ru/man.shtml?topic=tcsetattr&category=3&russian=2
*/
/*
#include <stdio.h>
#include <signal.h>
#include <termios.h> 
#include <unistd.h>

int main()
{
	int a;
	struct termios termios_p;

	a = 0;
	a = tcgetattr(0, &termios_p);
	if (a == 0)
	{
		
	}
	else
	{
		return (-1);
	}
	return (0);
}
*/
# include <stdio.h>
# include <termios.h> 
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>

int main()
{
	int i_stat;
    int i;
    char *path_and_command = "/bin/echo";
    struct stat stat_command;

	i_stat = 0;
	i_stat = stat(path_and_command, &stat_command);
	if (i_stat == 0)
	{
		if (S_ISREG(stat_command.st_mode))
		{
			if ((stat_command.st_mode & S_IWUSR) == S_IXUSR)
			{
				return (1);
			}
		}
	}
	return (0);
}



