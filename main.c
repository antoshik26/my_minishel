# include <stdio.h>
# include <termios.h> 
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
#include<string.h>
void	ft_putstr_fd(char *s, int fd)
{
	size_t i;

	i = 0;
	if (s)
		while (s[i] != '\0')
		{
			write(fd, &s[i], 1);
			i++;
		}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;
	char	*buf;

	if (!s1)
		return (NULL);
	len_s1 = 0;
	len_s2 = 0;
	i = 0;
	len_s1 = strlen(s1);
	len_s2 = strlen(s2);
	buf = (char *)malloc(sizeof(char) * (len_s1 + len_s2) + 1);
	if (buf == NULL)
		return (NULL);
	while (i < (len_s1 + len_s2))
	{
		if (i < len_s1)
			buf[i] = s1[i];
		else
			buf[i] = s2[i - len_s1];
		i++;
	}
	buf[i] = '\0';
	return (buf);
}
void ft_cd(char **argv,char **env)
{
	int i;
	char buf[32000];
	char *tmp;
	getcwd(buf,32000);
	i = -1;
//	printf("%s",argv);
	if(chdir(argv[1])==-1)
	{
		printf("wrong directory\n");
		return;
	}
	while(env[++i])
	{
		if(!strncmp(env[i],"OLDPWD=",7))
		{
			tmp=env[i];
			env[i]=ft_strjoin("OLDPWD=",buf);
			//printf("%s\n",env[i]);
			//free(tmp);
			break;
		}
	}
	getcwd(buf,32000);
	i=-1;
	while(env[++i])
	{
		if(!strncmp(env[i],"PWD=",4))
		{
			tmp=env[i];
			env[i]=ft_strjoin("PWD=",buf);
			//printf("%s\n",env[i]);
			//free(tmp);
			break;
		}
	}
	//free(buf);
	//exit(0);
}
int main(int argc,char **argv,char **env)
{
   ft_cd(argv,env);
   int i;
   i=-1;
   	while (env[++i])
	{	
		//if(!ft_strncmp(env[i],"_=/Users/lbones/Desktop/my_minishel_private/./a.out",52))
		//	ft_putstr_fd("_=/usr/bin/env",fd);
		//else
			ft_putstr_fd(env[i],0);
		putchar('\n');
	}
  while(1);

}