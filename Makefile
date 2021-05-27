NAME = minishell
CC = gcc
INCLUDE = -I include
HEADER = ./include/ft_minishell.h
FLAGS = -Wall -Wextra -Werror
PARSER = parser
COMMAND = command
SIGNALS = signals
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
	gcc -g ${FLAGS} ${INCLUDE} ${AUXILIARY_FUNCTIONS}/additional_features.c ${PARSER}/parser.c ${COMMAND}/command.c ${COMMAND}/stat_command.c ${SIGNALS}/signal_manager.c ft_minishell.c ./gnl/gnl.a

test_file:
	gcc -g minishell_test.c

clean:
		rm -f $(OBJS)

fclean:	
			rm -f $(OBJS) $(NAME)

re:			fclean all

.PHONY:
			all clean fclean re

