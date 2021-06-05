# include <stdio.h>
# include <termios.h> 
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
int main(int argc,char **argv,char **env)
{
    char buf[32000];
	
	getcwd(buf,32000);
    printf("%s",buf);
    if(chdir("gnl")==-1)
		exit(1);
    getcwd(buf,32000);
    printf("%s",buf);

}