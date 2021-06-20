#include "ft_minishell.h"

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