#include "ft_minishell.h"

void signal_manager(int sig)
{
    int i;

    i = 0;
    if (g_global_pid != 0 && sig == SIGINT)
    {
        kill(g_global_pid, sig);
        write(1, "\n", 1);
        g_global_pid = 0;
    }
    if (g_global_pid != 0 && sig == SIGQUIT)
    {
        kill(g_global_pid, sig);
        write(1, "Quit: 3\n", 8);
        g_global_pid = 0;
    }
    /*
    if (sig == SIGINT) //ctrl-c
    {
        if (g_global_pid != 0)
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
        if (g_global_pid != 0)
        {
            kill(g_global_pid, sig);
            write(1, "Quit: 3\n", 8);
            global_pid = 0;
        }
    }*/
}