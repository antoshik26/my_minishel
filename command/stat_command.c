#include "ft_minishell.h"

int check_stat_command_with_path(t_command_and_flag *command)
{
    int i_stat;
    struct stat stat_command;

    i_stat = 0;
    i_stat = stat(command->command, &stat_command);
    {   
        if (i_stat == 0)
        {
            if (S_ISREG(stat_command.st_mode))
            {
                if ((stat_command.st_mode & S_IXUSR) == S_IXUSR)
                    return (i_stat);
                else
                    i_stat = -1;
            }
            else
                i_stat = -1;
        }
    }
    return (i_stat);
}

int check_stat_file_with_path(t_command_and_flag *command)
{
    int i_stat;
    int i;
    struct stat stat_command;

    i = 0;
    i_stat = -1;
    i_stat = stat(command->command, &stat_command);
    if (i_stat == 0)
    {
        if (S_ISREG(stat_command.st_mode))
        {
            if (command->pape == LESS)
            {
                if ((stat_command.st_mode & S_IRUSR) == S_IRUSR)
                    return (i_stat);
                else
                    i_stat = -1;
            }
            else
            {
                if ((stat_command.st_mode & S_IWUSR) == S_IWUSR)
                    return (i_stat);
                else
                    i_stat = -1;
            }
        }
    }
    return (i_stat);
}

int check_stat_command(t_minishell *all_command, t_command_and_flag *command)
{
    int i_stat;
    int i;
    struct stat stat_command;
    char *path_and_command;
    
    i = 0;
    path_and_command = NULL;
    i_stat = -1;
    if (find_slash_dot(command->command) == 1)
       i_stat = check_stat_command_with_path(command);
    else
    {
        while(all_command->path[i])
        {
            path_and_command = ft_strjoin(all_command->path[i], command->command);
            i_stat = stat(path_and_command, &stat_command);
            if (i_stat == 0)
            {
                if (S_ISREG(stat_command.st_mode))
                {
                    if ((stat_command.st_mode & S_IXUSR) == S_IXUSR)
                        break ;
                    else
                        i_stat = -1;
                }
                else
                    i_stat = -1;
            }
            i++;
            free (path_and_command);
            path_and_command = NULL;
        }
    }
    if(path_and_command != NULL)
    {
        free(command->command);
        command->command = path_and_command;
    }
    return (i_stat);
}

int create_file(char *path_and_command)
{
    int i;
    int fd;

    i = 0;
    fd = open(path_and_command, O_WRONLY | O_CREAT, 0777 | O_TRUNC | O_APPEND);
    if (!fd)
        return (-1);
    else
        close(fd);
    return (0);
}

int check_stat_file(t_command_and_flag *command)
{
    int i_stat;
    int i;
    struct stat stat_command;
    int len;
    char buf[32000];
    
    i = 0;
    i_stat = -1;
    if (find_slash_dot(command->command) == 1)
        i_stat = check_stat_file_with_path(command);
    else
    {
        getcwd(buf,32000);
        len = ft_strlen(buf);
        buf[len] = '/';
        len++;
        buf[len] = '\0';
        command->command = ft_strjoin(buf, command->command);
        i_stat = stat(command->command, &stat_command);
        if (i_stat == 0)
        {
            if (S_ISREG(stat_command.st_mode))
            {
                if (command->pape == LESS)
                {
                    if ((stat_command.st_mode & S_IRUSR) == S_IRUSR)
                        return (i_stat);
                    else
                        i_stat = create_file(command->command);
                }
                else
                {
                    if ((stat_command.st_mode & S_IWUSR) == S_IWUSR)
                        return (i_stat);
                    else
                        i_stat = create_file(command->command);
                }
            }
            else
            {
                i_stat = -1;
            }
        }
        else
        {
            i_stat = create_file(command->command);
        }
    }
    return (i_stat);
}

int check_stat_build_in(t_command_and_flag *command)
{
    int stat;

    stat = -1;
    if (!ft_strncmp(command->command, "echo", 4) ||
    !ft_strncmp(command->command, "cd", 2) ||
    !ft_strncmp(command->command, "pwd", 3) ||
    !ft_strncmp(command->command, "minishell", 9) ||
    !ft_strncmp(command->command, "export", 6) ||
    !ft_strncmp(command->command, "unser", 5) ||
    !ft_strncmp(command->command, "env", 3) ||
    !ft_strncmp(command->command, "exit", 4))
    {
        stat = 1;
    }
    return (stat);
}

int *stat_command(t_minishell *all_command)
{
    int i_stat;
    t_command_and_flag *command;
    
    command = all_command->head;
    while (command)
    {
        i_stat = -1;
        /*
        if (check_stat_build_in(command) == 1)
        {
            command->f_error = 0;
            command = command->next;
            continue ; 
        }
        */
        if (command->pape == DOUBLE_MORE || command->pape == MORE || command->pape == LESS)
            i_stat = check_stat_file(command);
        else
            i_stat = check_stat_command(all_command, command);
        if (i_stat == 0)
            command->f_error = 0;
        else
            command->f_error = -1;
        command = command->next;
    }
    return (0);
}


