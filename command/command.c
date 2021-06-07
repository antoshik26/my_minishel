#include "ft_minishell.h"

void ft_pwd(char **env,int fd)
{
	int i;
	int i1;

	i = -1;
	while(env[++i])
	{
		if(!ft_strncmp(env[i],"PWD=",4))
		{
			i1=3;
			while(env[i][++i1])
				ft_putchar_fd(env[i][i1],fd);
			ft_putchar_fd('\n',fd);
			exit(0);
		}
	}
	char buf[32000];
	getcwd(buf,32000);
	ft_putstr_fd(buf,fd);
	exit(0);
}

void ft_env(char **env,int fd)
{
	int i;

	i = -1;
	while (env[++i])
	{	
		//if(!ft_strncmp(env[i],"_=/Users/lbones/Desktop/my_minishel_private/./a.out",52))
		//	ft_putstr_fd("_=/usr/bin/env",fd);
		//else
			ft_putstr_fd(env[i],fd);
		ft_putchar_fd('\n',fd);
	}
	exit(0);
}

void ft_cd(t_command_and_flag *all,char **env)
{
	int i;
	char buf[32000];
	char *tmp;
	getcwd(buf,32000);
	i = -1;
	ft_putstr_fd("sdfihbvjgfd \n", 0);
	//printf("%s",all->array_flags[1]);
	if(chdir(all->array_flags[1])==-1)
	{
		ft_putstr_fd("sdfihbvjgfd", 0);
		//printf("wrong directory\n");
		return;
	}
	while(env[++i])
	{
		if(!ft_strncmp(env[i],"OLDPWD=",7))
		{
			tmp=env[i];
			env[i]=ft_strjoin("OLDPWD=",buf);
			//printf("%s\n",env[i]);
			//free(tmp);
			break;
		}
	}
	ft_putstr_fd("sdfihbvjgfd\n", 0);
	getcwd(buf,32000);
	i=-1;
	while(env[++i])
	{
		if(!ft_strncmp(env[i],"PWD=",4))
		{
			tmp=env[i];
			env[i]=ft_strjoin("PWD=",buf);
			//printf("%s\n",env[i]);
			//free(tmp);
			break;
		}
	}
	ft_putstr_fd("sdfihbvjgfd\n ", 0);
	//free(buf);
	//exit(0);
}