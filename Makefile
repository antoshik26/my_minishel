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
GNL = gnl
SRCS =	${AUXILIARY_FUNCTIONS}/additional_features.c \
		${AUXILIARY_FUNCTIONS}/lists_for_execve.c \
		${CMD}/cmd_manager.c \
		${CMD}/reeder_from_term.c \
		${COMMAND}/command.c \
		${COMMAND}/execve.c \
		${COMMAND}/stat_command.c \
		${PARSER}/parser.c \
		${SIGNALS}/signal_manager.c \
		ft_minishell.c

OBJS =		${SRCS:.c=.o}

%.o: %.c
	$(CC) -o $(FLAGS) ${INCLUDE} -c $<  -o $(<:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS)
			@make re -C libft	
			@cp $(LIBA)/libft.a ./$(NAME)
			@make re -C gnl	
			@cp $(GNL)/gnl.a ./$(NAME)
			gcc -o $(NAME) $(OBJS) ${LIBA}/libft.a ${GNL}/gnl.a ${INCLUDE} -ltermcap
test:	
	gcc -g ${FLAGS} ${INCLUDE} ${AUXILIARY_FUNCTIONS}/additional_features.c ${PARSER}/parser.c ${COMMAND}/command.c ${COMMAND}/stat_command.c ${SIGNALS}/signal_manager.c ft_minishell.c ${COMMAND}/execve.c ${CMD}/cmd_manager.c ./gnl/gnl.a ./libft/ft_split.c ./libft/ft_strncmp.c ${AUXILIARY_FUNCTIONS}/lists_for_execve.c ${CMD}/reeder_from_term.c -ltermcap ./libft/ft_putchar_fd.c ./libft/ft_isdigit.c ./libft/ft_putstr_fd.c  ${AUXILIARY_FUNCTIONS}/array_of_strings.c ./libft/ft_putnbr_fd.c ${COMMAND}/export.c ./libft/ft_isalpha.c ./libft/ft_strnstr.c ./libft/ft_isalnum.c ./libft/ft_atoi.c ./libft/ft_itoa.c

test_file:
	gcc -g minishell_test.c

clean:
		rm -f $(OBJS)

fclean:	
			rm -f $(OBJS) $(NAME)

re:			fclean all

.PHONY:
			all clean fclean re

