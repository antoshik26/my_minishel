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
void	ft_echo(t_command_and_flag *all,int fd)
{
	int i=0;
	if(!all->array_flags[1])
	{	
		ft_putchar_fd('\n',fd);
		exit(0);
	}
	while(all->array_flags[++i])
	{
		ft_putstr_fd(all->array_flags[i],fd);
		ft_putchar_fd('\n',fd);
	}
	exit(0);
}
void ft_cd(t_command_and_flag *all,char **env)
{
	int i;
	char buf[32000];
	getcwd(buf,32000);
	i = -1;
	if(chdir(all->array_flags[1])==-1)
	{
		ft_putstr_fd("wrong directory:",0);
		ft_putstr_fd(all->array_flags[i],0);
		ft_putstr_fd("\n",0);
		return;
	}
	while(env[++i])
	{
		if(!ft_strncmp(env[i],"OLDPWD=",7))
		{
			env[i]=ft_strjoin("OLDPWD=",buf);
			break;
		}
	}
	getcwd(buf,32000);
	i=-1;
	while(env[++i])
	{
		if(!ft_strncmp(env[i],"PWD=",4))
		{
			env[i]=ft_strjoin("PWD=",buf);
			break;
		}
	}
}
void ft_export(t_command_and_flag *all,char **env,int fd)
{
	int i;
	int i1;
	char *name;
	char *value;

	i = -1;
	if(!all->array_flags[1])
	{
		while(env[++i])
		{
			i1 = 0;
			ft_putstr_fd("declare -x ",fd);
			while (env[i][i1] && env[i][i1]!='=')
				ft_putchar_fd(env[i][i1++],fd);
			ft_putchar_fd(env[i][i1],fd);
			ft_putchar_fd(34,fd);
			while (env[i][++i1])
				ft_putchar_fd(env[i][i1],fd);
			ft_putchar_fd(34,fd);
			ft_putchar_fd('\n',fd);		
		}
	}
	else
	{
		i1=0;
		while( all->array_flags[1][i1] && all->array_flags[1][i1]!='=')
			i1++;
		if(all->array_flags[1][i1]=='=')
			value=0;
		else
			value=&all->array_flags[1][i1+1];
		all->array_flags[1][i1]='\0';
		name=ft_strdup(&all->array_flags[1][i1]);
		
	}
}
int ft_check_equally(char *str,int len)
{
	if(str[len-1]=='=')
		return (0);
	while(str[len])
	{	
		if(str[len]=='=')
			return(1);
		len++;
	}
	return(0);
}
void ft_unset(t_command_and_flag *all,char **env)
{
	int i;
	int len;
	int i1;

	i1=0;
	i=0;
	if(!all->array_flags[1])
		return;
	len=ft_strlen(all->array_flags[1]);
	while(env[i]) 
	{
		if(!ft_strncmp(env[i],all->array_flags[1],len) && !ft_check_equally(env[i],len))
		{
			ft_putstr_fd(env[i],0);
			while(env[i+1])
			{
				env[i]=env[i+1];
				i++;
			}
			env[i]=env[i+1];
			break;
		}
		i++;
	}
	ft_putstr_fd(env[i],0);
/*	if(!ft_strncmp(env[i],all->array_flags[1],len) && !ft_check_equally(env[i],len))
	{
		ft_putstr_fd(env[i],0);
		while(env[i+1])
		{
			env[i]=env[i+1];
			i++;
		}
		env[i]=env[i+1];
	}*/
}