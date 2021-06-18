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

void ft_env(t_command_and_flag *all,char **env,int fd)
{
	int i;

	i = -1;
	if(all->array_flags[1])
		exit(1);
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
void	ft_double_less_print(t_command_and_flag *all,int fd)
{
	int i=1;
	while(all->array_flags[i])
	{
		ft_putstr_fd(all->array_flags[i++],fd);
		//if (all->array_flags[i])
		ft_putchar_fd('\n',fd);
	}
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
void ft_unset_loop(char *str,t_env *struct_env)
{
	int len;
	int i;

	i=0;
	if(ft_check_name(str))
	// unset
	{
		len=ft_strlen(str);
	//env
		while(struct_env->env[i]) 
		{
			if(!ft_strncmp(struct_env->env[i],str,len) && struct_env->env[i][len]=='=')
			{
				struct_env->env=new_array_rm(struct_env->env,i);
				struct_env->keys=new_array_rm(struct_env->keys,i);
				struct_env->values=new_array_rm(struct_env->values,i);
				break;
			}
			i++;
		}
		i=-1;
	//env_lvl
		if(!struct_env->env_lvl)
			return;
		while (struct_env->env_lvl[++i])
		{
			if(!ft_strncmp(struct_env->env_lvl[i],str,len) && struct_env->env_lvl[i][len]=='\0')
			{
				struct_env->env_lvl=new_array_rm(struct_env->env_lvl,i);
				break;
			}
		}
	}
}
int ft_unset(t_command_and_flag *all,t_env *struct_env/*,int flag*/)
{
	int i;
	int len;
	int i1;
	int num;

	num=0;
	i1=0;
	i=0;
	//errors
	if(!all->array_flags[1])
		return(0);
	while(all->array_flags[++num])
	{
		if(all->array_flags[num][0]=='$')
			ft_unset_loop(&all->array_flags[num][1],struct_env);
		else
			ft_unset_loop(all->array_flags[num],struct_env);
	}
	return(0);

}