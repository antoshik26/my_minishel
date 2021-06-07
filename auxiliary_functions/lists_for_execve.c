#include "ft_minishell.h"
t_command_and_flag	*ft_create_elem(t_command_and_flag *data)
{
	t_command_and_flag	 *elem;
	int i;

	i = 0;
	elem = (t_command_and_flag *)malloc(sizeof(t_command_and_flag));
	elem->pape=data->pape;
	elem->f_error=data->f_error;
	elem->command = ft_strdup(data->command);
	while(data->array_flags[i])
		i++;
	elem->array_flags=malloc(sizeof(char*)*(i+1));
	i=-1;
	while(data->array_flags[++i])
		elem->array_flags[i]=ft_strdup(data->array_flags[i]);
	elem->array_flags[i]=NULL;
	elem->next = 0;
	return (elem);
}
void	ft_list_push_front(t_command_and_flag **begin_list, t_command_and_flag *data)
{
	t_command_and_flag *elem;

	if (begin_list != 0)
	{
		elem = ft_create_elem(data);
		elem->next = *begin_list;
		*begin_list = elem;
	}
	else
		*begin_list = ft_create_elem(data);
}

void ft_list_clear(t_command_and_flag *command)
{
    int i;
    t_command_and_flag *tmp;

    while(command)
    {
		if(!command->f_error)
        free(command->command);
        i = 1;
       	while(command->array_flags[i])
        {
            free(command->array_flags[i]);
            i++;
        }
        free(command->array_flags);
        tmp = command->next;
        free(command);
        command = tmp;
    }
}