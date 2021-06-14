#include "ft_minishell.h"

void ft_pwd(t_command_and_flag *all,char **env,int fd)
{
	int i;
	int i1;

	i = -1;
	if(all->array_flags[1])
		exit(10);
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

void ft_env(t_command_and_flag *all,char **env,int fd)
{
	int i;

	i = -1;
	if(all->array_flags[1])
		exit(127);
	while (env[++i])
	{	
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
	while(!ft_strncmp(all->array_flags[++i],"-n",3));
	while(all->array_flags[i])
	{
		ft_putstr_fd(all->array_flags[i++],fd);
		if (all->array_flags[i])
			ft_putchar_fd(32,fd);
	}
	if(ft_strncmp(all->array_flags[1],"-n",3))
		ft_putchar_fd('\n',fd);
	exit(0);
}
int ft_cd(t_command_and_flag *all,char **env)
{
	int i;
	char buf[32000];
	getcwd(buf,32000);
	i = -1;
	if(chdir(all->array_flags[1])==-1)
		return (10);
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
	return(0);
}

int ft_unset(t_command_and_flag *all,t_env *struct_env/*,int flag*/)
{
	int i;
	int len;
	int i1;
	int flag=1;
	i1=0;
	i=0;
	if(!all->array_flags[1])
	{	
		ft_putstr_fd("unset: not enough arguments\n",0);//1
		return (10);
	}
	if(!ft_check_name(all->array_flags[1]))
	{	
		ft_putstr_fd("bash: export: nor valid",0);
		ft_putchar_fd('\n',0);
		return(2);
	}
	if(flag)
	{
	len=ft_strlen(all->array_flags[1]);
	while(struct_env->env[i]) 
	{
		if(!ft_strncmp(struct_env->env[i],all->array_flags[1],len) && struct_env->env[i][len]=='=')
		{
			struct_env->env=new_array_rm(struct_env->env,i);
			break;
		}
		i++;
	}
	i=-1;
	if(!struct_env->env_lvl)
		return(0);
	while (struct_env->env_lvl[++i])
	{
		if(!ft_strncmp(struct_env->env_lvl[i],all->array_flags[1],len) && struct_env->env_lvl[i][len]=='\0')
		{
			struct_env->env_lvl=new_array_rm(struct_env->env_lvl,i);
			break;
		}
	}}
	return(0);
	
}