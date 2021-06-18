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
   int i;

   i=0;
   while(env[i])
      printf("%s\n",env[i++]);
   printf("%s\n",env[i++]);

}