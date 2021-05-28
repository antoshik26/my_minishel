NAME = libft.a
CC = gcc
FLAGS = -Wall -Wextra -Werror
HEADER = libft.h
OPTION = -c -I $(HEADER)
SRCS =		ft_atoi.c   \
            	ft_bzero.c  \
            	ft_calloc.c \
            	ft_isalnum.c    \
            	ft_isalpha.c    \
            	ft_isascii.c    \
            	ft_isdigit.c    \
            	ft_isprint.c    \
            	ft_itoa.c   \
            	ft_memccpy.c    \
            	ft_memcmp.c \
            	ft_memchr.c \
            	ft_memcpy.c \
            	ft_memmove.c    \
            	ft_memset.c \
            	ft_putchar_fd.c \
            	ft_putendl_fd.c \
            	ft_putnbr_fd.c  \
            	ft_putstr_fd.c  \
            	ft_split.c  \
            	ft_strchr.c \
            	ft_strdup.c \
            	ft_strjoin.c    \
            	ft_strlcat.c    \
            	ft_strlcpy.c    \
            	ft_strlen.c \
            	ft_strmapi.c    \
            	ft_strncmp.c    \
            	ft_strnstr.c    \
            	ft_strrchr.c    \
            	ft_strtrim.c    \
            	ft_substr.c \
            	ft_tolower.c    \
            	ft_toupper.c

OBJS =		${SRCS:.c=.o}
	
SRCS_BONUS =	ft_lstnew.c   \
		ft_lstadd_front.c \
		ft_lstsize.c   \
		ft_lstlast.c   \
		ft_lstadd_back.c   \
		ft_lstdelone.c   \
		ft_lstclear.c   \
		ft_lstiter.c \
		ft_lstmap.c

OBJS_BONUS =	$(SRCS_BONUS:.c=.o)

all:		$(NAME)

$(NAME) :		${OBJS}
			$(CC) $(FLAGS) $(OPTION) $(SRCS)
			ar rc $(NAME) $(OBJS)
			ranlib $(NAME)

bonus:			${OBJS_BONUS}
			$(CC) $(FLAGS) $(OPTION) $(SRCS_BONUS)
			ar rc $(NAME) $(OBJS_BONUS)
			ranlib $(NAME)
clean:			
			rm -f $(OBJS) $(OBJS_BONUS)
fclean:
			rm -f $(NAME)
re:			fclean	all
re_bonus:		fclean all bonus	
.PHONY:		all clean fclean re bonus re_bonus
