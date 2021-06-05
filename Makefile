NAME = minishell
CC = gcc
INCLUDE = -I include
HEADER = ./include/ft_minishell.h
FLAGS = -Wall -Wextra -Werror
PARSER = parser
COMMAND = command
SIGNALS = signals
CMD = cmd_manager
AUXILIARY_FUNCTIONS = auxiliary_functions
LIBA = libft
SRCS =	${AUXILIARY_FUNCTIONS}/additional_features.c \
		${PARSER}/parser.c \
		${COMMAND}/command.c \
		${COMMAND}/stat_command.c \
		${SIGNALS}/signal_manager.c \
		ft_minishell.c

OBJS =		${SRCS:.c=.o}

%.o: %.c
	$(CC) -o $(FLAGS) ${INCLUDE} -c $<  -o $(<:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS)
			@make re -C libft	
			@cp $(LIBA)/libft.a ./$(NAME)
			gcc -o $(NAME) $(OBJS) ${INCLUDE}

test:
<<<<<<< HEAD
	gcc -g ${INCLUDE} ${AUXILIARY_FUNCTIONS}/additional_features.c ${PARSER}/parser.c ${COMMAND}/command.c ${COMMAND}/stat_command.c ${SIGNALS}/signal_manager.c ft_minishell.c ${COMMAND}/execve.c ${CMD}/cmd_manager.c ./gnl/gnl.a ./libft/ft_split.c ./libft/ft_strncmp.c ${AUXILIARY_FUNCTIONS}/lists_for_execve.c ./libft/ft_putchar_fd.c ./libft/ft_putstr_fd.c
=======
	gcc -g ${FLAGS} ${INCLUDE} ${AUXILIARY_FUNCTIONS}/additional_features.c ${PARSER}/parser.c ${COMMAND}/command.c ${COMMAND}/stat_command.c ${SIGNALS}/signal_manager.c ft_minishell.c ${COMMAND}/execve.c ${CMD}/cmd_manager.c ./gnl/gnl.a ./libft/ft_split.c ./libft/ft_strncmp.c ${AUXILIARY_FUNCTIONS}/lists_for_execve.c ${CMD}/reeder_from_term.c -ltermcap

>>>>>>> a56f6a0d7f4365a3f49e836e5ff9ecc63f48fa27

test_file:
	gcc -g minishell_test.c

clean:
		rm -f $(OBJS)

fclean:	
			rm -f $(OBJS) $(NAME)

re:			fclean all

.PHONY:
			all clean fclean re

