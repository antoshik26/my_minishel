#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# define DIRECT_LINE    1
# define MORE           2
# define DOUBLE_MORE    3 
# define LESS           4
# define SEMICOLON      5
# define END_FILE       6

typedef struct  s_command_and_flag
{
    char *command_and_flags;
    char *command;
    int num_proc;
    int pape;
    char *flags;
    char **array_flags;
    struct s_command_and_flag *next;
}               t_command_and_flag;

typedef struct s_minishell
{
    char *count_command[15];
    int onecovkey;
    int doublecovkey;
    t_command_and_flag *head;
    char **env;
}               t_minishell;


int parser_commands(char *command, t_minishell *all_command);



void                ft_lstadd_back(t_command_and_flag **lst, t_command_and_flag *new);
t_command_and_flag	*ft_lstnew(char *command, int pape);
size_t              ft_strlen(const char *s);
char                *ft_strjoin(char const *s1, char const *s2);
char                *create_command(char *command, int i, int j);
int                 get_next_line(int fd, char **line);
char                *create_cloth_cov(t_minishell *all_command, char *command_and_flags);
#endif