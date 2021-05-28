#include "ft_minishell.h"


int check_stat_command(t_minishell *all_command, t_command_and_flag *command)
{
    int i_stat;
    int i;
    struct stat stat_command;
    char *path_and_command;
    
    i = 0;
    while (all_command->path[i])
    {
        path_and_command = ft_strjoin(all_command->path[i], command->command);
        i_stat = stat(path_and_command, &stat_command);
        if (i_stat == 0)
        {
            if (S_ISREG(stat_command.st_mode))
            {
                if ((stat_command.st_mode & S_IXUSR) == S_IXUSR)
                    break;
                else
                    i_stat = -1;
            }
            else
                i_stat = -1;
        }
        i++;
        free(path_and_command);
    }
    command->path_and_command = path_and_command;
    return (i_stat);
}

int check_stat_file(t_minishell *all_command, t_command_and_flag *command)
{
    int i_stat;
    int i;
    struct stat stat_command;
    char *path_and_command;
    
    i = 0;
    while (all_command->path[i])
    {
        path_and_command = ft_strjoin(all_command->path[i], command->command);
        i_stat = stat(path_and_command, &stat_command);
        if (i_stat == 0)
        {
            if (S_ISREG(stat_command.st_mode))
            {
                if (command->pape == LESS)
                {
                    if ((stat_command.st_mode & S_IRUSR) == S_IRUSR)
                        break;
                    else
                        i_stat = -1;
                }
                else
                {
                    if ((stat_command.st_mode & S_IWUSR) == S_IWUSR)
                        break;
                    else
                        i_stat = -1;
                }
            }
            else
                i_stat = -1;
        }
        i++;
        free(path_and_command);
    }
    command->path_and_command = path_and_command;
    return (i_stat);
}

int *stat_command(t_minishell *all_command)
{
    int i_stat;
    t_command_and_flag *command;
    
    command = all_command->head;
    while (command)
    {
        i_stat = -1;
        if (command->pape == DOUBLE_MORE || command->pape == MORE || command->pape == LESS)
            i_stat = check_stat_file(all_command, command);
        else
            i_stat = check_stat_command(all_command, command);
        if (i_stat == 0)
            command->status_flag = -1;
        command = command->next;
    }
    return (0);
}


