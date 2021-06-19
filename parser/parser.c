#include "ft_minishell.h"

int ft_clear_command_from_kov(t_minishell *all_command, t_command_and_flag *command)
{
    int i;
    int j;
    int len;
    int k;

    j = 0;
    i = 0;
    while (command->command[i])
    {
        if (command->command[i] == '\'' && all_command->doublecovkey != 1)
        {
            if (all_command->onecovkey == 0)
                all_command->onecovkey = 1;
            else
                all_command->onecovkey = 0;
            j = i;
            k = 0;
            len = ft_strlen(&command->command[i]);
            while(k < len)
            {
                command->command[j] = command->command[j + 1];
                j++;
                k++;
            }
        }
        if (command->command[i] == '\"' && all_command->onecovkey != 1)
        {
            if (all_command->doublecovkey == 0)
                all_command->doublecovkey = 1;
            else
                all_command->doublecovkey = 0;
            j = i;
            k = 0;
            len = ft_strlen(&command->command[i]);
            while(k < len)
            {
                command->command[j] = command->command[j + 1];
                j++;
                k++;
            }
        }
        if (command->command[i] == '\0')
            break;
        i++;
    }
    return (0);
}

int ft_clear_flags_from_kov(t_minishell *all_command)
{
    int i;
    int j;
    int len;
    int k;
    int l;
    t_command_and_flag *command;

    command = all_command->head;
    while (command)
    {
        i = 0;
        if (command->array_flags != NULL)
        {
            while (command->array_flags[i])
            {
                j = 0;
                while (command->array_flags[i][j])
                {
                    if (command->array_flags[i][j] == '\'' && all_command->doublecovkey != 1)
                    {
                        if (all_command->onecovkey == 0)
                            all_command->onecovkey = 1;
                        else
                            all_command->onecovkey = 0;
                        l = j;
                        k = 0;
                        len = ft_strlen(&command->array_flags[i][j]);
                        while(k < len)
                        {
                            command->array_flags[i][l] = command->array_flags[i][l + 1];
                            l++;
                            k++;
                        }
                    }
                    if (command->array_flags[i][j] == '\"' && all_command->onecovkey != 1)
                    {
                        if (all_command->doublecovkey == 0)
                            all_command->doublecovkey = 1;
                        else
                            all_command->doublecovkey = 0;
                        l = j;
                        k = 0;
                        len = ft_strlen(&command->array_flags[i][j]);
                        while(k < len)
                        {
                            command->array_flags[i][l] = command->array_flags[i][l + 1];
                            l++;
                            k++;
                        }
                    }
                    j++;
                }
                i++;
            }  
        }
        command = command->next;
    }
    return (0);
}


int shift_comand(char *command, t_minishell *all_command)
{
    int i;
    int fd;
    char a[5];
    
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
    /*
    i = 1;
    while(i < 15)
    {
        all_command->count_command[i - 1] = all_command->count_command[i];
        i++;
    }
    all_command->count_command[0] = command;
    */
    return (0);
}

char *create_command_with_env_variables(char *command, t_minishell *all_command)
{
    int i;
    int j;
    char *env_varianles;
    char *name_varianled;
    char *tmp;

    i = 0;
    j = 0;
    tmp = NULL;
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
            i++;
        }
        if (command[i] == '\"' && all_command->onecovkey == 0)
        {
            if (all_command->doublecovkey == 0)
                all_command->doublecovkey = 1;
            else
                all_command->doublecovkey = 0;
            i++;
        }
        if (command[i] == '$' && all_command->onecovkey != 1)
        {  
            i++;
            j = i;
            while(command[i] != ' ' && command[i] != '\0')
            {
                i++;
            }
            if (!ft_strnstr(command, "unset", ft_strlen(command)))
            {
                name_varianled = create_command(command, i, j);
                env_varianles = my_getenv(name_varianled, all_command);
				all_command->env_varianles = env_varianles;
				all_command->name_varianled = name_varianled;
                tmp = replacement(command, &i, j--, all_command);
                command = tmp;
                free(name_varianled);
            }
        }
        if (command[i] == '\0')
            break ;
        i++;
    }
    if (tmp != NULL)
        free(tmp);
    return (command);
}

int create_null_array_flags(t_command_and_flag *command)
{
    command->array_flags[0] = command->command;
    return (0);
}


int split_flags(t_command_and_flag *one_command, t_minishell *all_command)
{
    int i;
    int j;
    int k;
    int l;

    i = 0;
    j = 0;
    l = 1;
    k = 0;
    while (one_command->flags[i])
    {
        if (l == 1)
        {
            while (one_command->flags[i] == ' ')
                i++;
            k = i;
            l = 0;
        }
        if (one_command->flags[i] == '\'' && all_command->doublecovkey == 0)
        {
            if (all_command->onecovkey == 0)
                all_command->onecovkey = 1;
            else
                all_command->onecovkey = 0;
            if (one_command->flags[i + 1] == '\0')
                j++;
            i++;
            continue ;
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
            continue ;
        }
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

int parser_flags(t_minishell *all_command)
{
    int i;
    int j;
    int k;
    int z;
    t_command_and_flag *one_command;

    one_command = all_command->head;
    while (one_command)
    {
        split_flags(one_command, all_command);
        create_null_array_flags(one_command);
        i = 0;
        k = 1;
        j = 0;
        z = 0;
        all_command->onecovkey = 0;
        all_command->doublecovkey = 0;
        while (one_command->flags[i])
        {
            while (one_command->flags[j] == ' ')
            {
                j++;
                i = j;
            }
            if (one_command->flags[j] == '\0')
                break;
            if (one_command->flags[i] == '\'' && all_command->doublecovkey == 0)
            {
                if (all_command->onecovkey == 0)
                    all_command->onecovkey = 1;
                else
                    all_command->onecovkey = 0;
                if (one_command->flags[i + 1] == '\0')
                {
                    i++;
                    one_command->array_flags[k] = (char *)malloc(sizeof(char) * (i - j + 1));
                    if (one_command->array_flags[k] == NULL)
                        return (-1);
                    z = 0;
                    while (j < i)
                    {
                        one_command->array_flags[k][z] = one_command->flags[j];
                        z++;
                        j++;
                    }
                    one_command->array_flags[k][z] = '\0';
                    k++;
                    j = i;
                    i++;
                    break ;
                }
            }
            if (one_command->flags[i] == '\"' && all_command->onecovkey == 0)
            {
                if (all_command->doublecovkey == 0)
                    all_command->doublecovkey = 1;
                else
                    all_command->doublecovkey = 0;
                if (one_command->flags[i + 1] == '\0')
                {
                    i++;
                    one_command->array_flags[k] = (char *)malloc(sizeof(char) * (i - j + 1));
                    if (one_command->array_flags[k] == NULL)
                        return (-1);
                    z = 0;
                    while (j < i)
                    {
                        one_command->array_flags[k][z] = one_command->flags[j];
                        z++;
                        j++;
                    }
                    one_command->array_flags[k][z] = '\0';
                    k++;
                    j = i;
                    i++;
                    break ;
                }
            }
            if ((one_command->flags[i] == ' ' && all_command->onecovkey != 1 && all_command->doublecovkey != 1 && j != i) || (one_command->flags[i + 1] == '\0'))
            {
                if (one_command->flags[i + 1] == '\0' && one_command->flags[i] != ' ')
                    i++;
                one_command->array_flags[k] = (char *)malloc(sizeof(char) * (i - j + 1));
                if (one_command->array_flags[k] == NULL)
                    return (-1);
                z = 0;
                while (j < i)
                {
                    one_command->array_flags[k][z] = one_command->flags[j];
                    z++;
                    j++;
                }
                one_command->array_flags[k][z] = '\0';
                k++;
                j = i;
                if (one_command->flags[i] == '\0')
                    break ;
            }
            i++;
        }
        one_command->array_flags[k] = NULL;
        one_command = one_command->next;
        ft_clear_flags_from_kov(all_command);
    }
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

int parser_command(t_minishell *all_command)
{
    int i;
    int j;
    int len;
    int k;
    t_command_and_flag *one_command;

    one_command = all_command->head;
    while(one_command)
    {
        i = 0;
        j = 0;
        len = ft_strlen(one_command->command_and_flags);
        while (one_command->command_and_flags[i] == ' ')
            i++;
        j = i;
        while (one_command->command_and_flags[i])
        {
            if (one_command->command_and_flags[i] == '\'' && all_command->doublecovkey == 0)
            {
                if (all_command->onecovkey == 0)
                    all_command->onecovkey = 1;
                else
                    all_command->onecovkey = 0;
                i++;
                continue ;
            }
            if (one_command->command_and_flags[i] == '\"' && all_command->onecovkey == 0)
            {
                if (all_command->doublecovkey == 0)
                    all_command->doublecovkey = 1;
                else
                    all_command->doublecovkey = 0;
                i++;
                continue ;
            }
            if (one_command->command_and_flags[i] == ' ' && all_command->onecovkey != 1 && all_command->doublecovkey != 1)
                break ;
            i++;
        }
        one_command->command = (char *)malloc(sizeof(char) * (i - j) + 1);
        if (one_command->command == NULL)
            return (-1);
        k = 0;
        while (j < i)
        {
            one_command->command[k] = one_command->command_and_flags[j];
            j++;
            k++;
        }
        one_command->command[j] = '\0';
        ft_clear_command_from_kov(all_command, one_command);
        j = 0;
        one_command->flags = (char *)malloc(sizeof(char) * (len - i + 1));
            if (one_command->flags == NULL)
                return (-1);
        while(i < len)
        {
            one_command->flags[j] = one_command->command_and_flags[i];
            j++;
            i++;
        }
        one_command->flags[j] = '\0';
        one_command = one_command->next;
    }
    stat_command(all_command);
    parser_flags(all_command);
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