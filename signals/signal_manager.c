#include "ft_minishell.h"

void signal_manager(int sig)
{
    int i;
    int global_pid;
    char *line;

    i = 0;
    global_pid = 0;
    if (sig == SIGINT) //ctrl-c
    {
        if (global_pid != 0)
        {
            write(1, "\n", 1);
        }
        else
        {
            line = NULL;
            get_next_line(0, &line);
            if (line == NULL)
            {
                
            }
            else
                write(1, "\n", 1);

        }
    }
    if (sig == SIGQUIT) //ctrl-/
    {
        if (global_pid != 0)
        {
            kill(global_pid, sig);
            write(1, "Quit: 3\n", 8);
            global_pid = 0;
        }
    }
}