#include "ft_minishell.h"

int *stat_command(t_minishell *all_command)
{
    int i_stat;
    int i;
    char *path_and_command;
    struct stat stat_command;
    t_command_and_flag *command;
    
    i = 0;
    command = all_command->head;
    while (command)
    {
        while (all_command->path[i])
        {
            i_stat = 0;
            path_and_command = ft_strjoin(all_command->path[i], command->command);
            i_stat = stat(path_and_command, &stat_command);
            if (i_stat == 0)
            {
                if (S_ISREG(stat_command.st_mode))
                {
                    if ((stat_command.st_mode & S_IXUSR) == S_IXUSR)
                    {
                        break;
                    }
                }
            }
            i++;
        }
        if (i_stat == 0)
        {
            command->status_flag = -1;
        }
        else
        {
            command->path_and_command = path_and_command;
        }
        command = command->next;
    }
    return (0);
}

