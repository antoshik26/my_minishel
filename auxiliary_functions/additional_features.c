#include "ft_minishell.h"

void	ft_lstadd_back(t_command_and_flag **lst, t_command_and_flag *new)
{
	t_command_and_flag *a;

	a = *lst;
	if (!*lst && new)
	{
		*lst = new;
	}
	while (a)
	{
		if (a->next == NULL)
		{
			a->next = new;
			break ;
		}
		else
			a = a->next;
	}
}

void	ft_lstadd_front(t_command_and_flag **lst, t_command_and_flag *new)
{
	new->next = *lst;
	*lst = new;
}

t_command_and_flag	*ft_lstnew(char *command, int pape)
{
	t_command_and_flag *new_list;

	new_list = (t_command_and_flag *)malloc(sizeof(t_command_and_flag));
	if (new_list == NULL)
		return (NULL);
	new_list->command_and_flags = command;
	new_list->command = NULL;
	new_list->pape = pape;
	new_list->flags = NULL;
	new_list->num_proc = 0;
	new_list->array_flags = NULL;
	new_list->next = NULL;
	return (new_list);
}


char *create_command(char *command, int i, int j)
{
	char *new_command;
	int k;
	
	k = 0;
	new_command = (char *)malloc(sizeof(char) * (i - j + 1));
	if (new_command == NULL)
		return (NULL);
	while(k < (i - j))
	{
		new_command[k] = command[j + k];
		k++;
	}
	new_command[k] = '\0';
	return (new_command);
}

char *create_cloth_cov(t_minishell *all_command, char *command_and_flags)
{
	char *new_command_and_flags;
	int len;
	int i;

	i = 0;
	len = ft_strlen(command_and_flags);
	new_command_and_flags = NULL;
	if (all_command->onecovkey == 1 && all_command->doublecovkey == 1)
	{
		while (len)
		{
			if (command_and_flags[len] == '\"')
			{
				new_command_and_flags = (char *)malloc(sizeof(char) * ft_strlen(command_and_flags) + 2);
				if (new_command_and_flags == NULL)
					return (NULL);
				while (command_and_flags[i])
				{
					new_command_and_flags[i] = command_and_flags[i];
					i++;
				}
				new_command_and_flags[i++] = '\"';
				new_command_and_flags[i++] = '\'';
				new_command_and_flags[i++] = '\0';
				break ;
			}
			if (command_and_flags[len] == '\'')
			{
				new_command_and_flags = (char *)malloc(sizeof(char) * ft_strlen(command_and_flags) + 2);
				if (new_command_and_flags == NULL)
					return (NULL);
				while (command_and_flags[i])
				{
					new_command_and_flags[i] = command_and_flags[i];
					i++;	
				}
				new_command_and_flags[i++] = '\'';
				new_command_and_flags[i++] = '\"';
				new_command_and_flags[i++] = '\0';
				break ;
			}
			len--;
		}
		all_command->onecovkey = 0;
		all_command->doublecovkey = 0;
	}
	if (all_command->onecovkey == 1)
	{
		new_command_and_flags = (char *)malloc(sizeof(char) * ft_strlen(command_and_flags) + 1);
		if (new_command_and_flags == NULL)
			return (NULL);
		while(command_and_flags[i])
		{
			new_command_and_flags[i] = command_and_flags[i];
			i++;
		}
		new_command_and_flags[i++] = '\'';
		new_command_and_flags[i] = '\0';
		all_command->onecovkey = 0;
	}
	if (all_command->doublecovkey == 1)
	{
		new_command_and_flags = (char *)malloc(sizeof(char) * ft_strlen(command_and_flags) + 1);
		if (new_command_and_flags == NULL)
			return (NULL);
		while(command_and_flags[i])
		{
			new_command_and_flags[i] = command_and_flags[i];
			i++;
		}
		new_command_and_flags[i++] = '\'';
		new_command_and_flags[i] = '\0';
		all_command->doublecovkey = 0;
	}
	return (new_command_and_flags);
}

char *replacement(char *command, int *i, int j, char* env_varianles, char *name_varianled, t_minishell *all_command)
{
	int k;
	int len_env;
	int len_command;
	int a;
	int c;
	char *new_command;

	len_command = 0;
	len_env = 0;
	a = 0;
	k = 0;
	if (env_varianles == NULL)
	{
		if (name_varianled[0] == '?' && ft_strlen(name_varianled) == 1)
		{
			a = all_command->env->exit_num;
			while (a > 0)
			{
				a = a / 10;
				len_env++;
			}
			if (all_command->env->exit_num == 0)
			{
				len_env = 1;
				env_varianles = (char *)malloc(sizeof(char) * len_env + 1);
				if (env_varianles == NULL)
					return (NULL);
				env_varianles[0] = '0';
				env_varianles[1] = '\0';
			}
			else
			{
				env_varianles = (char *)malloc(sizeof(char) * len_env + 1);
				if (env_varianles == NULL)
					return (NULL);
				env_varianles[len_env] = '\0';
				len_env--;
				while (len_env > -1)
				{
					env_varianles[len_env] = (all_command->env->exit_num % 10) + '0';
					all_command->env->exit_num = all_command->env->exit_num / 10;
					len_env--;
				}
			}
		}
		else
		{
			env_varianles = (char *)malloc(sizeof(char) * 1);
			if (env_varianles == NULL)
				return (NULL);
			env_varianles[0] = '\0';
		}
	}
	c = *i;
	k = j;
	a = c - j;
	len_command = ft_strlen(command);
	len_env = ft_strlen(env_varianles);
	while (k + a < len_command)
	{
		command[k] = command[k + a];
		k++;
	}
	command[k] = '\0';
	len_command = ft_strlen(command);
	new_command = (char *)malloc(sizeof(char) * (len_command + len_env + 1));
	if (new_command == NULL)
		return (NULL);
	k = 0;
	a = 0;
	c = j;
	while (k < len_command + len_env + 1)
	{
		if (k < (j - 1))
			new_command[k] = command[k];
		if (k > (j - 1) &&  k < j + len_env)
		{
			new_command[k - 1] = env_varianles[a];
			a++;
			(*i) = k;
		}
		if (k > j + len_env && command[c] != '\0')
		{
			new_command[k - 2] = command[c];
			c++;
		}
		k++;
	}
	k = k - 2;
	new_command[k] = '\0';
	if (name_varianled[0] == '?' && ft_strlen(name_varianled) == 1)
		free(env_varianles);
	free(new_command);
	return (new_command);
}

char  **find_path()
{
	char **path;
	char *tmp;
	int i;

	i = 0;

	tmp = getenv("PATH");
	path = ft_split(tmp,':');
	while (path[i])
	{
		tmp = path[i];
		path[i] = ft_strjoin(path[i], "/");
		free(tmp);
		i++;
	}
	return (path);
}

int find_slash_dot(char *line)
{
	int i;

	i = -1;
	while(line[++i])
	{
		if(line[i]==47)//47-ascii "\"
			return(1);
		else if(line[i]=='.')
			return(1);
	}
	return(0);
}

char *create_cislo_in_string(int lvl)
{
	char *chislo;
	int lvl_2;
	int i;

	i = 0;
	lvl_2 = lvl;
	while(lvl_2 > 0)
	{
		i++;
		lvl_2 = lvl_2 / 10;
	}
	lvl_2 = lvl;
	chislo = (char *)malloc(sizeof(char) * i + 1);
	if (chislo == NULL)
		return (NULL);
	chislo[i] = '\0';
	while(lvl_2)
	{
		chislo[i] = (lvl_2 % 10) + '0';
		lvl_2 = lvl_2 / 10;
		i--; 
	}
	return (chislo);
}

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

char *my_getenv(char *name_env, t_minishell *all_command)
{
	int i;

	i = 0;
	if (name_env[0] == '?')
		return (NULL);
	while (all_command->env->keys[i])
	{
		if (ft_strnstr(all_command->env->keys[i], name_env, ft_strlen(name_env)))
			break ;
		i++;
	}
	return (all_command->env->values[i]);
}

int create_env_lvl(t_env *env, int lvl)
{
	int i;
	int i1;
	char *new_lvl;
	char *tmp;

	i = 0;
	i1 = 0;
	new_lvl = ft_itoa(lvl);
	while(env->env[i])
	{
		if (ft_strnstr(env->env[i], "SHLVL", ft_strlen("SHLVL")))
		{
			while (env->env[i][i1] != '=')
			{
				i1++;
			}
			i1++;
			env->env[i][i1] = '\0';
			tmp = env->env[i];
			env->env[i] = ft_strjoin(env->env[i], new_lvl);
			free(tmp);
		}
		break ;
		i++;
	}
	//free(env->values[i]);
	//env->values[i] = new_lvl;
	free(new_lvl);
	return (0);
}

//написать strcmp
/*
int		ft_strcmp(const char *s1, const char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;

	i = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	while (i != (len_s1 + 1) || i != (len_s2 + 1))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
*/