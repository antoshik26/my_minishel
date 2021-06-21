#include "ft_minishell.h"

void	check_build_in(t_command_and_flag	*all, \
int	*pipe_1, int	fd1, t_env	*env)
{
	if ((!ft_strncmp(all->command, "/bin/pwd", 9) || \
	!ft_strncmp(all->command, "pwd", 4)) && fd1)
		ft_pwd(env->env, fd1);
	if (!ft_strncmp(all->command, "/bin/pwd", 9) && pipe_1 != 0)
		ft_pwd(env->env, pipe_1[1]);
	if (!ft_strncmp(all->command, "/bin/pwd", 9))
		ft_pwd(env->env, 0);
	if (!ft_strncmp(all->command, "/usr/bin/env", 13) && fd1)
		ft_env(all, env->env, fd1);
	if (!ft_strncmp(all->command, "/usr/bin/env", 13) && pipe_1 != 0)
		ft_env(all, env->env, pipe_1[1]);
	if (!ft_strncmp(all->command, "/usr/bin/env", 13))
		ft_env(all, env->env, 0);
	if (!ft_strncmp(all->command, "/bin/echo", 10) && fd1)
		ft_echo(all, fd1);
	if (!ft_strncmp(all->command, "/bin/echo", 10) && pipe_1 != 0)
		ft_echo(all, pipe_1[1]);
	if (!ft_strncmp(all->command, "/bin/echo", 10))
		ft_echo(all, 0);
}

void	check_build_in2(t_command_and_flag	*all, int	*pipe_1, \
int	fd1, t_env	*env)
{
	if (!ft_strncmp(all->command, "/usr/bin/cd", 13))
		exit(ft_cd(all, env->env));
	if (!ft_strncmp(all->command, "unset", 6))
		exit(ft_unset(all, env));
	if (!ft_strncmp(all->command, "export", 7) && fd1)
		exit(ft_export(all, fd1, env));
	if (!ft_strncmp(all->command, "export", 7) && pipe_1 != 0)
		exit(ft_export(all, pipe_1[1], env));
	if (!ft_strncmp(all->command, "export", 7))
		exit(ft_export(all, 0, env));
	if (all->pape == DOUBLE_LESS && fd1)
		ft_double_less_print(all, fd1);
	if (all->pape == DOUBLE_LESS && pipe_1 != 0)
		ft_double_less_print(all, pipe_1[1]);
	if (all->pape == DOUBLE_LESS)
		ft_double_less_print(all, 0);
}
