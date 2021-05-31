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
http://programming-lang.com/ru/comp_programming/metyu/0/j174.html
*/
typedef struct s_term_sistem
{
    struct termios *term;
}               t_term_sistem;

#include <stdio.h>
#include <signal.h>
#include <termios.h> 
#include <unistd.h>

int main()
{
	int a;
	t_term_sistem term;
	struct termios termios_p;

	a = 0;
	a = tcgetattr(0, &termios_p);
	if (a == 0)
	{
		term.term = &termios_p;
	}
	else
	{
		return (-1);
	}
	return (0);
}

/*
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
*/
/*
typedef struct s_pars
{
	char *filename;
	char **array;//NULL-terminated
	char **env;
}

void	ft_free(char **c)
{
	int	i;

	i = 0;
	while (c[i])
		free(c[i++]);
	free(c);
}

int	ft_len(int i, const char *s, char c)
{
	int	len;
	int	i3;

	i3 = i;
	len = 0;
	while (s[i])
	{
		while (s[i] != c && s[i])
			i++;
		if ((len == 0 || i != i3) || s[i])
			len++;
		while (s[i] == c && s[i])
			i++;
	}
	return (len);
}

char	**ft_fill(const char *s, char c, int i, char **s1)
{
	int	i3;
	int	len;
	int	i1;

	i1 = 0;
	i3 = 0;
	len = ft_len(i, s, c);
	while (len > i1)
	{
		i = i3;
		while (s[i++] == c)
			i3++;
		while (s[i] != c && s[i])
			i++;
		s1[i1] = ft_substr(s, i3, i - i3);
		if (!s1[i1])
		{
			ft_free(s1);
			return (NULL);
		}
		i3 = i;
		i1++;
	}
	return (s1);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		len;
	char	**s1;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] == c && s[i])
		i++;
	len = ft_len(i, s, c);
	s1 = (char **)malloc(sizeof(char *) * (len + 1));
	if (!s1)
		return (NULL);
	s1[len] = NULL;
	return (ft_fill(s, c, i, s1));
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	size_t	len1;
	size_t	len2;
	size_t	i;

	i = -1;
	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	s = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!s)
		return (NULL);
	while (++i < len1)
		s[i] = s1[i];
	i = 0;
	while (i < len2)
	{
		s[len1 + i] = s2[i];
		i++;
	}
	s[len1 + i] = '\0';
	return (s);
}
size_t	ft_strlen(char *a)
{
	size_t	i;

	i = 0;
	while (a[i])
		i++;
	return (i);
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*s1;
	size_t	i1;

	i1 = 0;
	if (!s)
		return (NULL);
	i = ft_strlen((char *)s);
	s1 = (char *)malloc(len + 1);
	if (!s1)
		return (NULL);
	while (i1 < len && start < i)
		s1[i1++] = s[start++];
	s1[i1] = '\0';
	return (s1);
}
char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*s2;
	size_t	i1;

	i1 = 0;
	i = ft_strlen((char *)s1);
	s2 = (char *)malloc(i + 1);
	if (!s2)
		return (NULL);
	while (i >= i1)
	{
		s2[i1] = s1[i1];
		i1++;
	}
	return (s2);
}

int ft_pwd(t_pars *all)
{
	int i;
	int i1;

	i = -1;
	if(all->array[1])
		return(1);
	while(all->env[i])
	{
		if(!strncmp(all->env[i],"PWD=",4))
		{
			i1=3;
			while(all->env[i][++i1])
				printf("%c",all->env[i][i1]);
			printf("\n");
			return(0);
		}
	}
	char buf[32000];
	getcwd(buf,32000);
	if(!buf)
		return(1);
	fprintf("%s",buf);
	return(0);
}

int ft_env(t_pars *all)
{
	int i;

	i = -1;
	if(all->array[1])
		return(1);
	while (all->env[++i])
		printf("%s\n",all->env[i]);
	return(0);
}

int ft_cd(t_pars *all)
{
	int i;
	char buf[32000];
	
	getcwd(buf,32000);
	if(!buf)
		return(1);
	i = -1;
	if(!all->array[1] || all->array[2])
		return(1);
	if(chdir(all->array[1])==-1)
		return(1);
	while(all->env[++i])
	{
		if(!strncmp(all->env[i],"OLDPWD=",7))
		{
			free(all->env[i]);
			all->env[i]=buf;
			break;
		}
	}
	getcwd(buf,32000);
	while(all->env[++i])
	{
		if(!strncmp(all->env[i],"PWD=",4))
		{
			free(all->env[i]);
			all->env[i]=buf;
			break;
		}
	}
	return(0);
}

int main(int argc,char **argv,char **env)
{
	int i;
	return (0);
}
*/