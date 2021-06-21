#include "ft_minishell.h"

void	free_tmp(t_command_and_flag	*tmp)
{	
	int	i;

	i = -1;
	free(tmp->command);
	while (tmp->array_flags[++i])
		free(tmp->array_flags[i]);
	free(tmp->array_flags[i]);
	free(tmp->array_flags);
	free(tmp);
}

void	redirect_pipe(int	*pipe, int	where)
{
	if (pipe != 0)
	{
		dup2(pipe[where], where);
		close(pipe[1]);
		close(pipe[0]);
	}
}

void	close_pipe(int	*pipe)
{
	if (pipe != 0)
	{
		close(pipe[1]);
		close(pipe[0]);
	}
}

void	free_find_fubction(int	**pipe, int	*pid)
{
	int	i;

	i = 0;
	free(pipe[i++]);
	while (pipe[i])
		free(pipe[i++]);
	free(pipe[i]);
	free(pipe);
	free(pid);
}
