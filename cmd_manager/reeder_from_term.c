#include "ft_minishell.h"

int create_term_win(t_minishell *all_command)
{
    struct winsize win;
    ioctl(1, TIOCGWINSZ, &win);
    all_command->win = &win;
    return (0);
}

int ft_strlen_history(t_minishell *all_command)
{
    int histori_slider;
    int fd;
    char *line;

    histori_slider = 0;
    fd = open(all_command->file_history, O_RDONLY);
    while (get_next_line(fd, &line) != 0)
    {
        free(line);
        histori_slider++;
    }
    free(line);
    close(fd);
    return (histori_slider);
}

char *reader_history_line(t_minishell *all_command, int histori_slider)
{
    char *history_line;
    int fd;
    int i;

    i = 0;
    fd = open(all_command->file_history, O_RDONLY);
    while (i < histori_slider)
    {
        get_next_line(fd, &history_line);
        free(history_line);
        i++;
    }
    get_next_line(fd, &history_line);
    close(fd);
    return (history_line);
}

char *reeder_from_term(t_minishell *all_command)
{   
    int len;
    int i;
    char *str;
    char *command;
    char *term_name;
    //char *tmp;
    int history_slider;
    char *history_line;
    void *a;
    int stat_1;
    struct termios termios_p_in;
    struct termios termios_und;

    tcgetattr(fileno(stdin), &termios_und);
    a = all_command;
    history_slider = 15;
    command = (char *)malloc(sizeof(char) * 1);
    command[0] = '\0';
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
    history_slider = ft_strlen_history(all_command);
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
            if (history_slider != 0)
            {
                history_line = reader_history_line(all_command, history_slider);
                write(1, history_line, ft_strlen(history_line));
                history_slider--;
                free(command);
                command = ft_strjoin(command, history_line);
                free(history_line);
            }
        }
        else if(!strcmp(str, "\e[B"))
        {
            tputs(restore_cursor, 1, ft_putchar);
            tputs(tigetstr("ed"), 1, ft_putchar);
            if (history_slider != MAX_LINE)
            {
                history_line = reader_history_line(all_command, history_slider);
                write(1, history_line, ft_strlen(history_line));
                history_slider++;
                free(command);
                command = ft_strjoin(command, history_line);
                free(history_line);
            }
        }
        else if (!strcmp(str, "\e[C"))
        {
            
        }
        else if (!strcmp(str, "\e[D"))
        {

        }
        else if (!strcmp(str, "\177"))
        {
            tputs(cursor_left, 1, ft_putchar);
            tputs(tgetstr("dc", 0), 1, ft_putchar);
            command[ft_strlen(command) - 1] = '\0';
        }
        else if (!strcmp(str, "\n"))
        {
            break ;
        }
        else if(!strcmp(str, "\4"))
        {
            if (ft_strlen(command) == 0)
                command = NULL;
            break ;
        }
        else
        {
            //tmp = command;
            command = ft_strjoin(command, str);
            //free(tmp);
            write(1, str, len);
            i++;    
        }
    }
    tcsetattr(fileno(stdin), TCSANOW, &termios_und);
    return(command);
}

