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

void create_cloth_cov()
{

}

/*
parser_array_flags(t_command_and_flag *command_and_flag)
{
    int i;
    int j;
    int len;
    t_command_and_flag *one_command;

    one_command = command_and_flag;
    while (one_command)
    {
        i = 0;
        j = 0;
        while (one_command->flags[i])
        {
            if (one_command->flags[i] == '' || one_command->flags == '')
                j++;
            i++;
        }
        one_command->array_flags = (char **)malloc(sizeof(char *) * (j + 1));
        if (one_command->array_flags == NULL)
            return (-1);
        i = 0;
        while (j > 0)
        {
            while ()
            {
                i++;
            }
            i = 0;
            one_command->array_flags[j] = (char *)malloc(sizeof(char) * (i + 1));
            if (one_command->array_flags[j] == NULL)
                return (-1);
            while (one_command->array_flags[j])
            {
                one_command->array_flags[j][i] = one_command->flags[i];
                i++;
            }
            j--;
        }
        one_command = one_command->next;
    }
    return (0);
}
*/
int create_list_command(char *command, t_minishell *all_command, int pipe)
{
    t_command_and_flag *new_command;
    new_command = ft_lstnew(command, pipe);
    ft_lstadd_back(&all_command->head, new_command);
    return (0);
}


int parser_flags(t_minishell *all_command)
{
    int i;
    int j;
    int k;
    int len;
    t_command_and_flag *one_command;

    one_command = all_command->head;
    while(one_command)
    {
        i = 0;
        j = 0;
        len = ft_strlen(command_and_flag->command_and_flags);
        while (one_command->command_and_flags[i])
        {
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
            {
                if (one_command->command_and_flags[i] == ' ' && all_command->onecovkey != 1 && all_command->doublecovkey != 1)
                    break ;
            }
            i++;
        }
        while (one_command->command_and_flags[i] != ' ' && one_command->command_and_flags[i])
        {
            j++;
            i++;
        }
        one_command->command = (char *)malloc(sizeof(char) * j + 1);
        i = i - j;
        k = j;
        j = 0;
        while (j < k)
        {
            one_command->command[j] = one_command->command_and_flags[i];
            i++;
            j++;
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
        one_command = one_command->next;
    }
    //parser_array_flags(command_and_flag);
    return (0);
}

int parser_commands(char *command, t_minishell *all_command)
{
    shift_comand(command, all_command);
    int i;
    char *new_command;
    int j;
    
    i = 0;
    j = 0;
    while (command[i])
    {
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
                create_list_command(new_command, all_command, DIRECT_LINE);
                i++;
                j = i;
            }
            if (command[i] == '>')
            {
                if (command[i + 1] == '>' )
                {
                    new_command = create_command(command, i, j);
                    create_list_command(new_command, all_command, DOUBLE_MORE);
                    i = i + 2;
                    j = i;
                }
                else
                {
                    new_command = create_command(command, i, j);
                    create_list_command(new_command, all_command, MORE);
                    i++;
                    j = i;
                }
            }
            if (command[i] == '<')
            {
                new_command = create_command(command, i, j);
                create_list_command(new_command, all_command, LESS);
                i++;
                j = i;
            }
            if (command[i] == ';')
            {
                new_command = create_command(command, i, j);
                create_list_command(new_command, all_command, SEMICOLON);
                i++;
                j = i;
            }
        }
        i++;
    }
    new_command = create_command(command, i, j);
    // if (all_command->onecovkey != 1 && all_command->doublecovkey != 1)
    //     create_cloth_cov();
    create_list_command(new_command, all_command, END_FILE);
    parser_flags(all_command);
    return (0);
}