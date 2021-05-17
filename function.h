#ifndef FUNCTION_H
# define FUNCTION_H
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <sys/stat.h>

typedef struct s_pars
{
	char *filename;
	char **array;//NULL-terminated
	char **env;
}				t_pars;
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(char *a);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	**ft_fill(const char *s, char c, int i, char **s1);
int	ft_len(int i, const char *s, char c);
void	ft_free(char **c);

#endif