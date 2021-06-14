#include "ft_minishell.h"

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

void clear_malloc(t_minishell *all_command)
{
    free(all_command->file_history);
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
    all_command->onecovkey = 0;
    all_command->doublecovkey = 0;
    all_command->exit = 255;
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
    char **a;

    a = argv;
    path = getenv("PWD");
    len = ft_strlen(path);
    path = ft_strjoin(path, "/tmp/lvl1");
    fd = open(path, O_WRONLY | O_CREAT, 0777 | O_TRUNC | O_APPEND);
    if (fd == -1)
        return (-1);
    all_command->file_history = path;
    close(fd);
    return (0);
}

void changes_path_history(t_minishell *all_command)
{
    int len;
    int i;
    //char *tmp;

    i = 0;
    len = ft_strlen(all_command->file_history);
    if (all_command->lvl < 10)
    {
        all_command->file_history[len -1] = all_command->lvl + '0';
    }/*
    else
    {
        i = len;
        while(ft_isdigit(all_command->file_history[i]))
            i--;
        
    }
    */
}
t_env *allocate_env(char **env)
{
    t_env *env1;
    env1=malloc(sizeof(t_env));
    env1->env=ft_strdup_array_of_strings(env);
    env1->env_lvl=0;
    return(env1);
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
    t_env *struct_env;
    struct_env=allocate_env(env);
    int lvl;
    if(!argv[1])
        lvl=0;
    else
        lvl=ft_atoi(argv[1]);
    printf("\nlvl1:%d\n",lvl);
    (void)argc;
    (void)argv;
    all_command.term_until[0] = &term_in_util;
    all_command.term_until[1] = &term_out_util;
    all_command.term[0] = &term_in;
    all_command.term[1] = &term_out;
    all_command.path = find_path();
    all_command.flag = 1;
    command = NULL;
    all_command.head = &command_and_flag;
    allocate(&all_command);
    crete_or_cheak_file_history(&all_command, argv);
    create_signal_controller();
    while(1 != 0)
    {
        all_command.path = find_path();
        command = cmd_manager(&all_command);
        if (command == NULL)
        {
            if (lvl == 0)
            {
                printf("%d\n", lvl);
                break;
            }
            else
            {
                lvl--;
                //changes_path_history(&all_command);
                write(1, "\n", 1);
            }
        }
        //нехватает системы lvlx 
        if (command != NULL)
        {
            parser_commands(command, &all_command);
            print_command(&all_command); //комманда для проверки парсера
            functions_launch(&all_command.head, struct_env,&lvl);
            free(command);
            rebut(&all_command);
        }
        
    }
    rebut(&all_command);
    clear_malloc(&all_command);
    //return_settings_term(&all_command);
    return (0);
}