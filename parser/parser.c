#include "ft_minishell.h"

int shift_comand(char *command, t_minishell *all_command)
{
    int i;

    i = 1;
    while(i < 15)
    {
        all_command->count_command[i - 1] = all_command->count_command[i];
        i++;
    }
    all_command->count_command[0] = command;
    return (0);
}

char *create_command_with_env_variables(char *command, t_minishell *all_command)
{
    int i;
    int j;
    char *env_varianles;
    char *name_varianled;

    i = 0;
    j = 0;
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
            while(command[i] != ' ' && command[i] != '\"')
            {
                i++;
            }
            name_varianled = create_command(command, i, j);
            env_varianles = getenv(name_varianled);
            command = replacement(command, &i, j--, env_varianles);
        }
        i++;
    }
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

    i = 0;
    j = 0;
    while (one_command->flags[i] == ' ')
        i++;
    while (one_command->flags[i])
    {
        if (one_command->command_and_flags[i] == '\'' && all_command->doublecovkey == 0)
        {
            if (all_command->onecovkey == 0)
                all_command->onecovkey = 1;
            else
                all_command->onecovkey = 0;
            i++;
        }
        if (one_command->command_and_flags[i] == '\"' && all_command->onecovkey == 0)
        {
            if (all_command->doublecovkey == 0)
                all_command->doublecovkey = 1;
            else
                all_command->doublecovkey = 0;
            i++;
        }
        if ((one_command->flags[i] == ' ' && all_command->onecovkey != 1 && all_command->doublecovkey != 1) || (one_command->flags[i + 1] == '\0'))
            j++;
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
                i++;
            }
            if (one_command->command_and_flags[i] == '\'' && all_command->doublecovkey == 0)
            {
                if (all_command->onecovkey == 0)
                    all_command->onecovkey = 1;
                else
                    all_command->onecovkey = 0;
                i++;
            }
            if (one_command->command_and_flags[i] == '\"' && all_command->onecovkey == 0)
            {
                if (all_command->doublecovkey == 0)
                    all_command->doublecovkey = 1;
                else
                    all_command->doublecovkey = 0;
                i++;
            }
            if ((one_command->flags[i] == ' ' && all_command->onecovkey != 1 && all_command->doublecovkey != 1) || one_command->flags[i + 1] == '\0')
            {
                if (one_command->flags[i + 1] == '\0')
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
            }
            i++;
        }
        one_command->array_flags[k] = NULL;
        one_command = one_command->next;
    }
    return (0);
}

int create_list_command(char *command, t_minishell *all_command, int pipe)
{
    t_command_and_flag *new_command;
    new_command = ft_lstnew(command, pipe);
    ft_lstadd_front(&all_command->head, new_command);
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
            }
            if (one_command->command_and_flags[i] == '\"' && all_command->onecovkey == 0)
            {
                if (all_command->doublecovkey == 0)
                    all_command->doublecovkey = 1;
                else
                    all_command->doublecovkey = 0;
                i++;
            }
            if (one_command->command_and_flags[i] == ' ' && all_command->onecovkey != 1 && all_command->doublecovkey != 1)
                break ;
            i++;
        }
        one_command->command = (char *)malloc(sizeof(char) * (i - j) + 1);
        k = 0;
        while (j < i)
        {
            one_command->command[k] = one_command->command_and_flags[j];
            j++;
            k++;
        }
        one_command->command[j] = '\0';
        j = 0;
        one_command->flags = (char *)malloc(sizeof(char) * (len - i + 1));
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
                new_command = create_command(command, i, j);
                create_list_command(new_command, all_command, pipe);
                pipe = LESS;
                i++;
                j = i;
            }
            if (command[i] == ';')
            {
                new_command = create_command(command, i, j);
                create_list_command(new_command, all_command, pipe);
                pipe = SEMICOLON;
                i++;
                j = i;
            }
        }
        i++;
    }
    new_command = create_command(command, i, j);
    if (all_command->onecovkey == 1 || all_command->doublecovkey == 1)
    {
       tmp = new_command;
       new_command = create_cloth_cov(all_command, new_command);
       free(tmp);
    }

    create_list_command(new_command, all_command, pipe);
    parser_command(all_command);
    return (0);
}