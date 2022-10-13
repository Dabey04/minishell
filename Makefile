NAME			=	minishell

SRCS			=	srcs/minishell.c \
					srcs/utils.c \

OBJS			=	${SRCS:.c=.o}

CC				=	clang #-Weverything -fsanitize=thread -g

CFLAGS			=	-Wall -Werror -Wextra

.c.o			:
					${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME)			:	${OBJS}
					${CC} ${OBJS} -o ${NAME}

all				:	${NAME}

clean			:
					@rm -rf ${OBJS}

fclean			:	clean
					@rm -rf ${NAME}

re				:	fclean all

.PHONY			:	all clean fclean re