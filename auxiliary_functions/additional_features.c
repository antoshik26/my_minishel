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
