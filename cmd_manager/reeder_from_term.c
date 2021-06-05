#include "ft_minishell.h"

int create_term_win(t_minishell *all_command)
{
    struct winsize win;
    ioctl(1, TIOCGWINSZ, &win);
    all_command->win = &win;
    return (0);
}
/*
int ft_strlen_history(t_minishell *all_command)
{
    int histori_slider;

    histori_slider = 0;
    return (histori_slider);
}

char *reader_history_line(t_minishell *all_command)
{
    char *history_line;

    return ();
}
*/
char *reeder_from_term(t_minishell *all_command)
{   
    int len;
    int i;
    char *str;
    char *term_name;
    int histori_slider;
    //char *history_line;
    void *a;
    int stat_1;
    struct termios termios_p_in;

    a = all_command;
    histori_slider = 15;
    if (!isatty(fileno(stdin)))
        return (NULL);
    term_name = getenv("TERM");
    if (term_name == NULL)
    {
        term_name = "xterm-256color";
    }
    stat_1 = tcgetattr(0, &termios_p_in);
    termios_p_in.c_lflag &= ~(ICANON);
    termios_p_in.c_lflag &= ~(ECHO);
    tcsetattr(0, TCSANOW, &termios_p_in);
    tgetent(0, term_name);
    //histori_slider = ft_strlen_history(all_command);
    str = (char *)malloc(sizeof(char) * 101);
    i = 0;
    //https://docs.google.com/document/d/1OzX0XRMcIUvCoE5ZTidod0K6yN3Kfs0wH0k-jTz45Lk/edit#
    //tputs(tgoto(tgetstr("cm", &buffer), 2, 2), 1, ft_putint);
    tputs(save_cursor, 1, ft_putchar);
    while (1 != 0)
    {
        len = read(0, str, 100);
        str[len] = '\0';
        if(!strcmp(str, "\e[A"))
        {
            tputs(restore_cursor, 1, ft_putchar);
            tputs(tigetstr("ed"), 1, ft_putchar);
            if (histori_slider == 0)
            {
                /*
                history_line = reader_history_line(all_command);
                write(1, history_line, ft_strlen(history_line));
                history_slider--;
                */
            }
            /*
            else
            {
                
            }
            */
        }
        if(!strcmp(str, "\e[B"))
        {
            tputs(restore_cursor, 1, ft_putchar);
            tputs(tigetstr("ed"), 1, ft_putchar);
            if (histori_slider != MAX_LINE)
            {
                /*
                history_line = reader_history_line(all_command);
                write(1, &history_line, ft_strlen(history_line));
                histori_slider++;
                */
            }
            /*
            else if(histori_slider == MAX_LINE)
            {

            }
            */
        }
        /*
        if (!ft_strcmp(str, "\e["))
        {

        }
        if (!ft_strcmp(str, "\e"));
        {

        }
        */
        if (!strcmp(str, "\177"))
        {
            tputs(cursor_left, 1, ft_putchar);
            tputs(tigetstr("dc"), 1, ft_putchar);
        }
        if (!strcmp(str, "\n"))
            break ;
        if(!strcmp(str, "\4"))
            break ;
        write(1, str, len);
        i++;
    }
    return(str);
}

