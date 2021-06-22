#include "ft_minishell.h"

void create_signal_controller()
{
    signal(SIGINT, &signal_manager);
	g_global_pid = 0;
	signal(SIGQUIT, &signal_manager);
}

int crete_or_cheak_file_history(t_minishell *all_command,  int lvl)
{
    char *path;
    int len;
    int fd;
    char *tmp;
    char *itoa;

    path = getenv("PWD");
    len = ft_strlen(path);
    path = ft_strjoin(path, "/tmp/lvl");
    tmp = path;
    itoa = ft_itoa(lvl);
    path = ft_strjoin(path, itoa);
    free(tmp);
    free(itoa);
    fd = open(path, O_WRONLY | O_CREAT, 0777 | O_TRUNC | O_APPEND);
    if (fd == -1)
        return (-1);
    all_command->file_history = path;
    close(fd);
    return (0);
}

int changes_path_history(t_minishell *all_command, int lvl)
{
    int len;
    int i;
    int fd;

    i = 0;
    len = ft_strlen(all_command->file_history);
    if (lvl < 10)
    {
        all_command->file_history[len -1] = lvl + '0';
        fd = open(all_command->file_history, O_WRONLY | O_CREAT, 0777 | O_TRUNC | O_APPEND);
        if (fd == -1)
            return (-1);
        close(fd);
    }
    return (0);
}

t_env *env_keys_values(t_env *env1,int lvl)
{
    int i;
    int i1;
    char *tmp;

    i = -1;
	while (env1->env[++i])
	{
        i1=-1;
        while(env1->env[i][++i1]!='='){};
        env1->env[i][i1]='\0';
        env1->keys[i]=ft_strdup(env1->env[i]);
        env1->env[i][i1]='=';
        if(!ft_strncmp(env1->keys[i],"SHLVL",6))
        {   
            env1->env[i][i1+1]='\0';
            env1->values[i]=ft_itoa(lvl+1);
            tmp=env1->env[i];
            env1->env[i]=ft_strjoin(tmp,env1->values[i]);
            free(tmp);
        }
        else
            env1->values[i]=ft_strdup(&env1->env[i][++i1]);
    }
    env1->values[i]=NULL;
    env1->keys[i]=NULL;
    return(env1);
}

t_env *allocate_env(char **env,int lvl)
{
    t_env *env1;
    int i;
    int i1;
    char *tmp;

    i = -1;
    env1 = malloc(sizeof(t_env));
    if (env1 == NULL)
        return (NULL);
    env1->env = ft_strdup_array_of_strings(env);
    env1->env_lvl=0;
    while (env[++i]){};
    env1->keys = (char **)malloc(sizeof(char *) * (i + 1));
    if(env1->keys == NULL)
        return (NULL);
	env1->values=(char **)malloc(sizeof(char *) * (i + 1));
    if (env1->values == NULL)
        return (NULL);
    i=-1;
	while (env[++i])
	{
        i1=-1;
        while(env[i][++i1]!='='){};
        env1->env[i][i1]='\0';
        env1->keys[i]=ft_strdup(env1->env[i]);
        env1->env[i][i1]='=';
        if(!ft_strncmp(env1->keys[i],"SHLVL",6))
        {   
            env1->env[i][i1+1]='\0';
            env1->values[i]=ft_itoa(lvl+1);
            tmp=env1->env[i];
            env1->env[i]=ft_strjoin(tmp,env1->values[i]);
            free(tmp);
        }
        else
            env1->values[i]=ft_strdup(&env1->env[i][++i1]);
        printf("k:%s v:%s\n",env1->keys[i],env1->values[i]);
    }
    env1->values[i]=NULL;
    env1->keys[i]=NULL;
   // env1=env_keys_values(env1,lvl);
    env1->exit_num=0;
    return(env1);
}

int find_path_from_new_env(t_minishell *all_command)
{
    int i;
    char *tmp;
    char *path;
    int len;
    int j;

    i = 0;
    j = 0;
    len = 0;
    path = NULL;
    while (all_command->env->keys[i])
    {
        if (ft_strnstr(all_command->env->keys[i], "PATH", ft_strlen(all_command->env->keys[i])))
        {
            len = ft_strlen(all_command->env->values[i]);
            path = (char *)malloc(sizeof(char) * (len + 1));
            while (j < len)
            {
                path[j] = all_command->env->values[i][j];
                j++;
            }
	        all_command->path = ft_split(path,':');
            i = 0;
	        while (all_command->path[i])
	        {
		        tmp = all_command->path[i];
		        all_command->path[i] = ft_strjoin(all_command->path[i], "/");
		        free(tmp);
		        i++;
	        }
            break ;
        }
        i++;
    }
    if (path == NULL)
        all_command->path = NULL;
    else
        free(path);
    return (0);
}

void allocate(t_minishell *all_command)
{
    all_command->onecovkey = 0;
    all_command->doublecovkey = 0;
    all_command->head = NULL;
}

int main_dup(int argc,char **argv,char **env)
{
    t_minishell all_command;
    t_command_and_flag command_and_flag;
    char *command;
    t_term_sistem term;
    t_env *struct_env;

    all_command.ret=-1;
    if(!argv[1])
        all_command.lvl=0;
    else
        all_command.lvl=ft_atoi(argv[1]);
    struct_env=allocate_env(env, all_command.lvl);
    create_env_lvl(struct_env, all_command.lvl);
    printf("\nlvl1:%d\n", all_command.lvl);
    (void)argc;
    (void)argv;
    all_command.flag = 1;
	all_command.term = &term;
    all_command.env = struct_env;
    command = NULL;
    all_command.head = &command_and_flag;
    all_command.path = find_path();
    allocate(&all_command);
    crete_or_cheak_file_history(&all_command, all_command.lvl);
    create_signal_controller();
    while(1 != 0)
    {
        errno = 0;
        command = cmd_manager(&all_command);
        if (command == NULL)
        {
            if (all_command.lvl == 0)
                break;
            else
            {
                all_command.lvl--;
                changes_path_history(&all_command, all_command.lvl);
                write(1, "\n", 1);
                all_command.ret=0;
                break;
            }
        }
        if (command != NULL)
        {
            if (ft_strlen(command) != 0)
            {
                parser_commands(command, &all_command);
                print_command(&all_command); //комманда для проверки парсера
                    free(command);
                all_command.ret=functions_launch(&all_command.head, struct_env, &all_command.lvl);
                if(all_command.ret!=-1)
                    break;
                rebut(&all_command);
            }
        }
        find_path_from_new_env(&all_command);
    }
    rebut(&all_command);
    clear_malloc(&all_command,all_command.env);
    ft_putstr_fd("exit\n",0);
    return (all_command.ret);
}

int main(int argc,char **argv,char **env)
{
    if(!argv[1])
        return(main_dup(argc,argv,env));
    else
        ft_putstr_fd("Error:too many arguments\n",0);
}