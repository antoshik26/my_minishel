#include "ft_minishell.h"
void    free_command(t_command_and_flag	*command)
{
    t_command_and_flag	*tmp;
    int					i;

    while(command)
    {
        free(command->command_and_flags);
        free(command->command);
        free(command->flags);
        i = 1;
        if (command->array_flags != NULL)
        {
            while(command->array_flags[i])
                free(command->array_flags[i++]);
            free(command->array_flags);
        }
        tmp = command->next;
        free(command);
        command = tmp;
    }

}
void	rebut(t_minishell	*all_command)
{
	int					i;
	t_command_and_flag	*command;
	t_command_and_flag	*tmp;

    all_command->onecovkey = 0;
    all_command->doublecovkey = 0;
    command = all_command->head;
    free_command(command);
    while(command)
    {
        free(command->command_and_flags);
        free(command->command);
        free(command->flags);
        i = 1;
        if (command->array_flags != NULL)
        {
            while(command->array_flags[i])
                free(command->array_flags[i++]);
            free(command->array_flags);
        }
        tmp = command->next;
        free(command);
        command = tmp;
    }
    if (all_command->path != NULL)
    {
        i = 0;
        while (all_command->path[i])
            free(all_command->path[i++]);
        free(all_command->path);
    }
    all_command->head = NULL;
}

void	clear_malloc(t_minishell	*all_command, t_env	*env)
{
	int	i;

	i = 0;
	free(all_command->file_history);
	while (env->env[i])
	{
		free(env->env[i]);
		free(env->keys[i]);
		free(env->values[i++]);
	}
	i = 0;
	free(env->env);
	free(env->keys);
	free(env->values);
	if (env->env_lvl != NULL)
	{
		while (env->env_lvl[i])
			free(env->env_lvl[i++]);
		free(env->env_lvl);
	}
	free(env);
}
