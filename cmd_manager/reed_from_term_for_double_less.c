#include "ft_minishell.h"

char	*term_from_double_less(void)
{
	int				len;
	int				i;
	char			*str;
	char			*command;
	char			*term_name;
	char			*tmp;
	int				stat_1;
	struct termios	termios_p_in;
	struct termios	termios_und;

	tcgetattr(fileno(stdin), &termios_und);
	command = (char *)malloc(sizeof(char) * 1);
	if (command == NULL)
		return (NULL);
	command[0] = '\0';
	if (!isatty(fileno(stdin)))
		return (NULL);
	term_name = getenv("TERM");
	if (term_name == NULL)
		term_name = "xterm-256color";
	stat_1 = tcgetattr(0, &termios_p_in);
	termios_p_in.c_lflag &= ~(ICANON);
	termios_p_in.c_lflag &= ~(ECHO);
	termios_p_in.c_lflag &= ~(ISIG);
	tcsetattr(0, TCSANOW, &termios_p_in);
	tgetent(0, term_name);
	str = (char *)malloc(sizeof(char) * 101);
	if (str == NULL)
		return (NULL);
	i = 0;
	write(1, "> ", 2);
	tputs(save_cursor, 1, ft_putchar);
	while (1 != 0)
	{
		len = read(0, str, 100);
		str[len] = '\0';
		if (!strcmp(str, "\e[A"))
		{
		}
		else if (!strcmp(str, "\e[B"))
		{
		}
		else if (!strcmp(str, "\e[C"))
		{
		}
		else if (!strcmp(str, "\e[D"))
		{
		}
		else if (!strcmp(str, "\t"))
		{
		}
		else if (!strcmp(str, "\177"))
		{
			if (i != 0)
			{
				tputs(cursor_left, 1, ft_putchar);
				tputs(tgetstr("dc", 0), 1, ft_putchar);
				command[ft_strlen(command) - 1] = '\0';
				i--;
			}
		}
		else if (!strcmp(str, "\n"))
		{
			write(1, "\n", 1);
			break ;
		}
		else if (!strcmp(str, "\4"))
		{
			if (ft_strlen(command) == 0)
			{
				free(command);
				command = NULL;
				break ;
			}
		}
		else if (!strcmp(str, "\3"))
		{
			tputs(restore_cursor, 1, ft_putchar);
			tputs(tigetstr("ed"), 1, ft_putchar);
			write(1, "\n", 1);
			free(command);
			command = malloc(sizeof(char) * 1);
			if (command == NULL)
				return (NULL);
			command[0] = '\0';
			break ;
		}
		else
		{
			tmp = command;
			command = ft_strjoin(command, str);
			free(tmp);
			write(1, str, len);
			i++;
		}
	}
	tcsetattr(fileno(stdin), TCSANOW, &termios_und);
	free(str);
	return (command);
}
