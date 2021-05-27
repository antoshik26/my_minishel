#include "ft_minishell.h"

void rebut(t_minishell *all_command)
{
    int i;
    t_command_and_flag *command;
    t_command_and_flag *tmp;

    command = all_command->head;
    while(command)
    {
        free(command->command_and_flags);
        free(command->command);
        free(command->flags);
        i = 0;
        while(command->array_flags[i])
        {
            free(command->array_flags[i]);
            i++;
        }
        free(command->array_flags);
        tmp = command->next;
        free(command);
        command = tmp;
    }
    all_command->head = NULL;
}

void create_signal_controller()
{
    signal(SIGINT, signal_manager);
}

void allocate(t_minishell *all_command)
{
    int i;

    i = 0;
    while (i < 15)
    {
        all_command->count_command[i] = NULL;
        i++;
    }
    all_command->env = NULL;
    all_command->onecovkey = 0;
    all_command->doublecovkey = 0;
    all_command->head = NULL;
}

//команда для проверки парсера перед сдачей удалить
void print_command(t_minishell *command_list)
{
    t_command_and_flag *command;
    int i;

    command = command_list->head;
    while (command)
    {
        printf("%s\n", command->command_and_flags);
        printf("%s\n", command->command);
        printf("%s\n", command->flags);
        i = 0;
        while (command->array_flags[i])
        {
            printf("%s\n", command->array_flags[i]);   
            i++;
        }
        command = command->next;
    }

}


int main(void)
{
    t_minishell all_command;
    t_command_and_flag command_and_flag;
    char *command;

    command = "\0";
    all_command.head = &command_and_flag;
    allocate(&all_command);
    create_signal_controller();
    while(1 != 0)
    {
        get_next_line(0, &command);
        if (command != NULL)
        {
            parser_commands(command, &all_command);
            print_command(&all_command); //комманда для проверки парсера
            rebut(&all_command);
        }
    }
    rebut(&all_command);
    return (0);
}