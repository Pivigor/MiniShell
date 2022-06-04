SRCS		=	ft_atoi.c					\
				ft_itoa.c					\
				ft_lstadd_back.c			\
				ft_lstclear.c				\
				ft_lstlast.c				\
				ft_lstnew.c					\
				ft_lstsize.c				\
				ft_split.c					\
				ft_strchr.c					\
				ft_strdup.c					\
				ft_strjoin.c				\
				ft_strlen.c					\
				ft_strncmp.c				\
				get_next_line_utils.c		\
				get_next_line.c				\
				main.c						\
				my_builtin.c				\
				my_builtin2.c				\
				my_cmd_parser_helper.c		\
				my_cmd_parser_parts.c		\
				my_cmd_parser.c				\
				my_executer_helper.c		\
				my_executer.c				\
				my_split_controlls_helper.c	\
				my_split_controlls.c		\
				my_status_solver_helper.c	\
				my_status_solver.c
OBJS		= ${SRCS:.c=.o}
DEPS		= ${SRCS:.c=.d}
NAME		= minishell
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
DEPFLAGS	= -MMD -MF ${<:.c=.d}
RM			= rm -f

all:		${NAME}

$(NAME):	${OBJS}
			${CC} -o ${NAME} ${OBJS}  -lreadline -I/Users/jgarlic/.brew/Cellar/readline/8.1.2/include -L/Users/jgarlic/.brew/Cellar/readline/8.1.2/lib

-include ${DEPS}

%.o:		%.c
			${CC} ${CFLAGS} -c $< ${DEPFLAGS} -I/Users/jgarlic/.brew/Cellar/readline/8.1.2/include

clean:
			${RM} ${OBJS} ${DEPS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
