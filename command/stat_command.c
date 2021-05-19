#include "ft_minishell.h"

char *stat_command(t_minishell *all_command)
{
    int i_stat;
    int i;
    char *command;
    char *path_and_command;
    struct stat stat_command;
    
    i = 0;
    i_stat = 0;
    while (all_command->path[i])
    {
        path_and_command = ft_strjoin(all_command->path[i], command);
        i_stat = stat(path_and_command, &stat_command);
        if (i_stat == 1)
        {
            if (stat_command.st_mode)
            {
                if (stat_command.st_size)
                {
                    break;
                }
            }
        }
        i++;
    }
    return (path_and_command);
}