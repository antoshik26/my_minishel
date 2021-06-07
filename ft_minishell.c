#include "ft_minishell.h"

int  g_global_pid;

void rebut(t_minishell *all_command)
{
    int i;
    t_command_and_flag *command;
    t_command_and_flag *tmp;

    all_command->onecovkey = 0;
    all_command->doublecovkey = 0;
    command = all_command->head;
    while(command)
    {
        free(command->command_and_flags);
        free(command->command);
        free(command->flags);
        i = 1;
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
    signal(SIGINT, &signal_manager);
	g_global_pid = 0;
	signal(SIGQUIT, &signal_manager);
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
        printf("\n");
        printf("command name:|%s|\n", command->command);
        printf("pape:%d\n", command->pape);
        printf("error:%d\n",command->f_error);
        i = 0;
        while (command->array_flags[i])
        {
            printf("ar[%d]:|%s|\n",i, command->array_flags[i]);   
            i++;
        }
        printf("ar[%d]:%s\n",i,command->array_flags[i]);
        command = command->next;
    }

}

int crete_or_cheak_file_history(t_minishell *all_command, char **argv)
{
    char *path;
    int len;
    int fd;

    path = argv[0];
    len = ft_strlen(path);
    while(len)
    {
        if (path[len] == '/')
        {
            path[len] = '\0';
            break ;
        }
        len--;
    }
    path = ft_strjoin(path, "/tmp/lvl1");
    fd = open(path, O_WRONLY | O_CREAT, 0777 | O_TRUNC | O_APPEND);
    if (fd == -1)
        return (-1);
    all_command->file_history = path;
    close(fd);
    return (0);
}

int main(int argc,char **argv,char **env)
{
    t_minishell all_command;
    t_command_and_flag command_and_flag;
    char *command;
    t_term_sistem term_in_util;
    t_term_sistem term_out_util;
    t_term_sistem term_in;
    t_term_sistem term_out;
    (void)argc;
    (void)argv;
    all_command.term_until[0] = &term_in_util;
    all_command.term_until[1] = &term_out_util;
    all_command.term[0] = &term_in;
    all_command.term[1] = &term_out;
    all_command.path = find_path();
    all_command.flag = 1;
    all_command.lvl = 0;
    command = NULL;
    all_command.head = &command_and_flag;
    allocate(&all_command);
    crete_or_cheak_file_history(&all_command, argv);
    //create_signal_controller();
    while(1 != 0)
    {
        command = cmd_manager(&all_command);
        //return_settings_term(&all_command);
        //get_next_line(0, &command);
        if (command == NULL)
        {
            if (all_command.lvl == 0)
            {
                break;
            }
            else
            {
                all_command.lvl--;
            }
        }
        //нехватает системы lvlx 
        if (ft_strlen(command) != 0 && command != NULL)
        {
            parser_commands(command, &all_command);
            print_command(&all_command); //комманда для проверки парсера
            functions_launch(&all_command.head, env);
            free(command);
            rebut(&all_command);
        }
        
    }
    rebut(&all_command);
    //return_settings_term(&all_command);
    return (0);
}