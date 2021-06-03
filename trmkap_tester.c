#include <curses.h>
#include <term.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char    room_termtype[2048];
char    *termtype;
char    buf[100];
char    *buffer;
 
int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

//необходима для tputs
int         ft_putint(int c)
{
   return (write(STDOUT_FILENO, &c, 1));
}
 
int         main(int argc, char **argv)
{
   //define the terminal
    if (!isatty(STDIN_FILENO))
       return(1);
   //чтобы было удобнее тестировать, будут использоваться аргументы
   /*
   if (argc < 2)
       return (1);
    */
    termtype = getenv("TERM");
    if (termtype == NULL || tgetent(room_termtype, termtype) != 1) 
       return (1);
    printf("%s\n", "save");
    tputs(save_cursor, 1, ft_putchar);
    printf("%s\n", "save_2");
   //далее будут вызываться функции
   return (0);
}
