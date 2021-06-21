#include "ft_minishell.h"

int split_flags_utils(t_command_and_flag *one_command, int *l, int *i, int *k)
{
	if (*l == 1)
	{
		while (one_command->flags[i] == ' ')
			*i++;
		*k = *i;
		*l = 0;
	}
	return (0);
}

int split_flags_utils2(t_command_and_flag *one_command, t_minishell *all_command, int *i, int *j)
{
	if (one_command->flags[i] == '\'' && all_command->doublecovkey == 0)
	{
		if (all_command->onecovkey == 0)
			all_command->onecovkey = 1;
		else
			all_command->onecovkey = 0;
		if (one_command->flags[i + 1] == '\0')
			j++;
		i++;
		return (1);
	}
	if (one_command->flags[i] == '\"' && all_command->onecovkey == 0)
	{
		if (all_command->doublecovkey == 0)
			all_command->doublecovkey = 1;
		else
			all_command->doublecovkey = 0;
		if (one_command->flags[i + 1] == '\0')
			j++;
		i++;
		return (1);
    }
	return (0);
}

int split_flags_utils3(t_command_and_flag *one_command, t_minishell *all_command)
{
	if ((one_command->flags[i] == ' ' && all_command->onecovkey != 1 && all_command->doublecovkey != 1 && i != k) || (one_command->flags[i + 1] == '\0'))
	{
		j++;
		l = 1;
	}
	return (0);
}

int split_flags(t_command_and_flag *one_command, t_minishell *all_command)
{
    int i;
    int j;
    int k;
    int l;
	int key;

    i = 0;
    j = 0;
    l = 1;
    k = 0;
    while (one_command->flags[i])
    {
		key = 0;
        split_flags_utils(one_command, &l, &i, &k);
		key = split_flags_utils2(one_command, all_command);
		if (key = 1)
			continue ;
        key = split_flags_utils2(one_command, all_command);
		if (key = 1)
			continue ;
        if ((one_command->flags[i] == ' ' && all_command->onecovkey != 1 && all_command->doublecovkey != 1 && i != k) || (one_command->flags[i + 1] == '\0'))
        {
            j++;
            l = 1;
        }
        i++;
    }
    one_command->array_flags = (char **)malloc(sizeof(char *) * (j + 2));
    if (one_command->array_flags == NULL)
        return (-1);
    return (0);
}