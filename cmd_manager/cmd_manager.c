#include "ft_minishell.h"

int cmd_manager()//t_minishell *all_command)
{
    struct termios terminal;

    tcgetattr(0, &terminal);
    //поменять пораметры терминала

    tcsetattr(0, TCSANOW, &terminal);
    return (0);
}