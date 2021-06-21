#include "ft_minishell.h"

int	shift_comand(char *command, t_minishell *all_command)
{
	int		i;
	int		fd;
	char	a[5];

	fd = open(all_command->file_history, O_RDWR);
	if (fd == -1)
		return (-1);
	i = 1;
	while (i != 0)
		i = read(fd, a, 1);
	if (all_command->flag == 1)
	{
		write(fd, "\n", 1);
		write(fd, command, ft_strlen(command));
		all_command->flag = 0;
	}
	else
	{
		write(fd, "\n", 1);
		write(fd, command, ft_strlen(command));
	}
	close(fd);
	return (0);
}

int create_null_array_flags(t_command_and_flag *command)
{
    command->array_flags[0] = command->command;
    return (0);
}

int create_list_command(char *command, t_minishell *all_command, int pipe)
{
    t_command_and_flag *new_command;
    new_command = ft_lstnew(command, pipe);
    // ft_lstadd_front(&all_command->head, new_command);
    ft_lstadd_back(&all_command->head, new_command);
    return (0);
}

int parser_commands(char *command, t_minishell *all_command)
{
    shift_comand(command, all_command);
    command = create_command_with_env_variables(command, all_command);
    int i;
    char *new_command;
    int j;
    char *tmp;
    int pipe;
    
    i = 0;
    j = 0;
    pipe = NEW_COMMAND;
    while (command[i])
    {
        if (command[i] == '\\')
        {
            i++;
            if (command[i] == '\'' || command[i] == '\"' || command[i] == '\\' || command[i] == '$')
            {
                i++;
            }
        }
        if (command[i] == '\'' && all_command->doublecovkey == 0)
        {
            if (all_command->onecovkey == 0)
                all_command->onecovkey = 1;
            else
                all_command->onecovkey = 0;
            if (command[i + 1] == '\0')
                break;
            i++;
            
        }
        if (command[i] == '\"' && all_command->onecovkey == 0)
        {
            if (all_command->doublecovkey == 0)
                all_command->doublecovkey = 1;
            else
                all_command->doublecovkey = 0;
            if (command[i + 1] == '\0')
                break;
            i++;
        }
        if (all_command->onecovkey != 1 && all_command->doublecovkey != 1)
        {
            if (command[i] == '|')
            {
                new_command = create_command(command, i, j);
                create_list_command(new_command, all_command, pipe);
                pipe = DIRECT_LINE;
                i++;
                j = i;
            }
            if (command[i] == '>')
            {
                if (command[i + 1] == '>' )
                {
                    new_command = create_command(command, i, j);
                    create_list_command(new_command, all_command, pipe);
                    pipe = DOUBLE_MORE;
                    i = i + 2;
                    j = i;
                }
                else
                {
                    new_command = create_command(command, i, j);
                    create_list_command(new_command, all_command, pipe);
                    pipe = MORE;
                    i++;
                    j = i;
                }
            }
            if (command[i] == '<')
            {
                if (command[i + 1] == '<')
                {
                    new_command = create_command(command, i, j);
                    create_list_command(new_command, all_command, pipe);
                    pipe = DOUBLE_LESS;
                    i = i + 2;
                    j = i;
                }
                else
                {
                    new_command = create_command(command, i, j);
                    create_list_command(new_command, all_command, pipe);
                    pipe = LESS;
                    i++;
                    j = i;
                }
                
            }
            /*
            if (command[i] == ';')
            {
                new_command = create_command(command, i, j);
                create_list_command(new_command, all_command, pipe);
                pipe = SEMICOLON;
                i++;
                j = i;
            }
            */
        }
        i++;
    }
    new_command = create_command(command, i, j);
    // if (all_command->onecovkey == 1 || all_command->doublecovkey == 1)
    // {
    //    tmp = new_command;
    //    new_command = create_cloth_cov(all_command, new_command);
    //    free(tmp);
    // }
    create_list_command(new_command, all_command, pipe);
    parser_command(all_command);
    return (0);
}