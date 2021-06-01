#include "ft_minishell.h"

int save_sistem_term(t_minishell *all_command)
{
    int stat_1;
    int stat_2;
    struct termios termios_p_in;
    struct termios termios_p_out;

    stat_1 = tcgetattr(fileno(stdin), &termios_p_in);
    stat_2 = tcgetattr(fileno(stdout), &termios_p_out);
    if (stat_1 == 0 && stat_2 == 0)
    {
        all_command->term_until[0]->term = &termios_p_in;
        all_command->term_until[1]->term = &termios_p_out;
    }
    else
    {
        return (-1);
    }
    return (0);
}

int create_new_sistem_term(t_minishell *all_command)
{
    int stat_1;
    int stat_2;
    struct termios termios_p_in;
    struct termios termios_p_out;

    stat_1 = tcgetattr(fileno(stdin), &termios_p_in);
    stat_2 = tcgetattr(fileno(stdout), &termios_p_out);
    if (stat_1 == 0 && stat_2 == 0)
    {
        all_command->term[0]->term = &termios_p_in;
        all_command->term[1]->term = &termios_p_out;

    }
    else
    {
        return (-1);
    }
    return (0);
}

int return_settings_term(t_minishell *all_command)
{
    tcsetattr(fileno(stdin), TCSANOW, all_command->term_until[0]->term);
    tcsetattr(fileno(stdout), TCSANOW, all_command->term_until[1]->term);
    return(0);
}

int cmd_manager(t_minishell *all_command)
{
    save_sistem_term(all_command);
    create_new_sistem_term(all_command);
    all_command->term[0]->term->c_lflag = all_command->term[0]->term->c_lflag | ICANON;
    all_command->term[0]->term->c_lflag = all_command->term[0]->term->c_lflag | VKILL;
    all_command->term[0]->term->c_lflag = all_command->term[0]->term->c_lflag | VQUIT;
    all_command->term[0]->term->c_lflag = all_command->term[0]->term->c_lflag | VINTR;
    all_command->term[0]->term->c_oflag = all_command->term[0]->term->c_oflag | ONOCR;
    all_command->term[0]->term->c_oflag = all_command->term[0]->term->c_oflag | ONLRET;
    all_command->term[0]->term->c_oflag = all_command->term[0]->term->c_oflag | OPOST;
    /*
    unsigned char command_signal = (unsigned char)(signal_manager);
    //all_command->term[1]->term->c_iflag = all_command->term[1]->term->c_iflag | INLCR;
    all_command->term[1]->term->c_cflag = all_command->term[1]->term->c_cflag | CREAD;
    */
    tcsetattr(fileno(stdin), TCSANOW, all_command->term[0]->term);
    tcsetattr(fileno(stdout), TCSANOW, all_command->term[1]->term);
    return (0);
}