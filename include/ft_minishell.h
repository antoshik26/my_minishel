#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H
# include <stdio.h>
# include <termios.h> 
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# define NEW_COMMAND    0
# define DIRECT_LINE    1
# define MORE           2
# define DOUBLE_MORE    3 
# define LESS           4
# define SEMICOLON      5

typedef struct s_term_sistem
{
    struct termios *term;
}               t_term_sistem;

typedef struct  s_command_and_flag
{
    char *command_and_flags;
    char *command;
    int num_proc;
    int pape;
    char *flags;
    char **array_flags;
    int f_error;
    int status_flag;
    struct s_command_and_flag *next;
}               t_command_and_flag;

typedef struct s_minishell
{
    char *count_command[15];
    int onecovkey;
    int doublecovkey;
    t_command_and_flag *head;
    t_term_sistem *term[2];
    char **env;
    char **path;
    int  g_global_pid; //как же криво работают сигналы
}               t_minishell;

int parser_commands(char *command, t_minishell *all_command);

void                functions_launch(t_command_and_flag **head,char **env);
int                 *stat_command(t_minishell *all_command);
char			    **ft_split(char const *s, char c);
char                **find_path();
void                ft_lstadd_back(t_command_and_flag **lst, t_command_and_flag *new);
t_command_and_flag	*ft_lstnew(char *command, int pape);
size_t              ft_strlen(const char *s);
char                *ft_strjoin(char const *s1, char const *s2);
char                *create_command(char *command, int i, int j);
int                 get_next_line(int fd, char **line);
char                *create_cloth_cov(t_minishell *all_command, char *command_and_flags);
char                *replacement(char *command, int *i, int j, char* env_varianles);
void                 signal_manager(int sig);
void                ft_lstadd_front(t_command_and_flag **lst, t_command_and_flag *new);
int                 find_slash_dot(char *line);
char                *ft_strdup(const char *s1);
int                 ft_pwd(t_minishell *all);
int                 ft_env(t_minishell *all);
int                 ft_cd(t_minishell *all);
int                 ft_strncmp(const char *s1, const char *s2, size_t n);
int                 cmd_manager();
int                 return_settings_term(t_minishell *all_command);
#endif