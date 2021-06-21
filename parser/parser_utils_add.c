#include "ft_minishell.h"

int	split_flags_utils5(t_command_and_flag *one_command, int j)
{
	one_command->array_flags = (char **)malloc(sizeof(char *) * (j + 2));
	if (one_command->array_flags == NULL)
		return (-1);
	return (0);
}
