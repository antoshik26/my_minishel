#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H
# include <stdio.h>
# include <curses.h>
# include <termios.h> 
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <term.h>
# include <string.h>
# include <errno.h>
# define MAX_LINE       15
# define NEW_COMMAND    0
# define DIRECT_LINE    1
# define MORE           2
# define DOUBLE_MORE    3 
# define LESS           4
# define SEMICOLON      5
# define DOUBLE_LESS    6
# define WRONG_COMMAND  -1
# define WRONG_FILE     -2    
# define PERMISSION_DENIED -3
extern int errno;  
pid_t  g_global_pid; //как же криво работают сигналы
typedef struct s_env
{
    char **env;
    char **keys;
    char **values;
    char **env_lvl;
    int exit_num;
}              t_env;
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
    char *file_history;
    int onecovkey;
    int doublecovkey;
    int flag;
    t_command_and_flag *head;
    t_term_sistem *term[2];
    t_term_sistem *term_until[2];
    struct winsize *win;
    char **path;
    t_env *env;
}               t_minishell;


typedef struct s_list_pid
{
    pid_t   *pid;
    int size;
    struct s_list_pid *next;
}               t_list_pid;
int                 parser_commands(char *command, t_minishell *all_command);
void                ft_putchar_fd(char c, int fd);
void                ft_putstr_fd(char *s, int fd);;
int functions_launch(t_command_and_flag **head,t_env *struct_env,int *lvl);
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
char                *replacement(char *command, int *i, int j, char* env_varianles, char *name_varianled, t_minishell *all_command);
void                signal_manager(int sig);
char                *create_cislo_in_string(int lvl);
void                ft_lstadd_front(t_command_and_flag **lst, t_command_and_flag *new);
int                 find_slash_dot(char *line);
char                *ft_strdup(const char *s1);
char                *ft_itoa(int n);
int                 ft_atoi(const char *str);
void                ft_pwd(t_command_and_flag *all,char **env,int fd);
void                ft_env(t_command_and_flag *all,char **env,int fd);
int                 ft_cd(t_command_and_flag *all,char **env);
void                ft_export(t_command_and_flag *all,int fd,t_env *struct_env);
int                 ft_unset(t_command_and_flag *all,t_env *struct_env/*,int flag*/);
void                ft_echo(t_command_and_flag *all,int fd);
int                 ft_strncmp(const char *s1, const char *s2, size_t n);
char                *cmd_manager(t_minishell *all_command);
int                 return_settings_term(t_minishell *all_command);
int                 ft_isdigit(int c);
char                *ft_strnstr(const char *haystack, const char *needle, size_t len);
char                *term_from_double_less();
char                *my_getenv(char *name_env, t_minishell *all_command);
//lists for ececbw
t_command_and_flag	*ft_create_elem(t_command_and_flag *data);
void                ft_list_push_front(t_command_and_flag **begin_list, t_command_and_flag *data);
void                ft_list_clear(t_command_and_flag *command);
char                *reeder_from_term(t_minishell *all_command);
int                 ft_putchar(int c);
//array 
void                free_array_of_strings(char **array);
char                **new_array_add(char **array,char *str);
char                **new_array_rm(char **array,int index);
char                **ft_strdup_array_of_strings(char **env);
int                 ft_check_name(char *name);
void			    ft_putnbr_fd(int n, int fd);
int                 ft_isalpha(int c);
int                 ft_isalnum(int c);
int                 main_dup(int argc,char **argv,char **env);
void                ft_list_push_second(t_command_and_flag **begin_list, t_command_and_flag *data);
void                ft_double_less_print(t_command_and_flag *all,int fd);

#endif