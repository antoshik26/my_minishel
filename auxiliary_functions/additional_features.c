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
