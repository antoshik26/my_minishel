#include "ft_minishell.h"
void ft_export_no_arguments(char **env,char **env_lvl,int fd)
{
	int i;
	int i1;

	i = -1;
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
	i=-1;
	while(env_lvl && env_lvl[++i])
	{
		ft_putstr_fd("declare -x ",fd);
		ft_putstr_fd(env_lvl[i],fd);
		ft_putchar_fd('\n',fd);	
	}
}
void	ft_export_find_name_value(t_command_and_flag *all,char **name,char **value)
{
	int i1;
	i1=0;
	while( all->array_flags[1][i1] && all->array_flags[1][i1]!='=')
		i1++;
	if(all->array_flags[1][i1]!='=')
		*value=0;
	else
		*value=&all->array_flags[1][i1+1];
	all->array_flags[1][i1]='\0';
	*name=ft_strdup(all->array_flags[1]);

}
int ft_check_name(char *name)
{
	int i;

	i=0;
	if(!ft_isalpha(name[0])&& name[0]!='_')
		return(0);
	while (name[++i])
	{
		if(!ft_isalnum(name[i]) && name[i]!='_')
			return(0);
	}
	return(1);
}
/*ft_sort_alph()
{
	int i;
	int max;
	while()
}*/

void ft_export(t_command_and_flag *all,int fd,t_env *struct_env)
{
	int i;
	char *name;
	char *value;
    int len;
	i = -1;
	if(!all->array_flags[1])
		ft_export_no_arguments(struct_env->env,struct_env->env_lvl,fd);
	else
	{
		ft_export_find_name_value(all,&name,&value);
		if(!ft_check_name(name))
		{	
			ft_putstr_fd("bash: export: nor valid",0);
			ft_putchar_fd('\n',0);
			return;
		}
        len=ft_strlen(name);
		while(struct_env->env[++i])
        {
            if(!ft_strncmp(struct_env->env[i],name,len) && struct_env->env[i][len] && struct_env->env[i][len]=='=')
            {
                if(value)
                {   
                    struct_env->env[i][len+1]='\0';
                    struct_env->env[i]=ft_strjoin(struct_env->env[i],value);
                }
                return;
            }
        }
		i=-1;
		while (struct_env->env_lvl && struct_env->env_lvl[++i])
		{
			if(!ft_strncmp(struct_env->env_lvl[i],name,len) && struct_env->env_lvl[i][len]=='\0')
			{
				if(value)
				{
					struct_env->env_lvl = new_array_rm(struct_env->env_lvl,i);
					name=ft_strjoin(name,"=");
					struct_env->env = new_array_add(struct_env->env,ft_strjoin(name,value));
				}
				return;
			}
		}
		if(!value)
			struct_env->env_lvl=new_array_add(struct_env->env_lvl,all->array_flags[1]);
		else
		{
			name=ft_strjoin(name,"=");
			struct_env->env=new_array_add(struct_env->env,ft_strjoin(name,value));
		}

	}
}