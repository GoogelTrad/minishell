NAME = minishell
CFLAGS = -Wall -Wextra -Werror
CC = gcc
RM = rm -f

SRCS = src/main.c src/prompt.c src/parsing.c src/builtins.c src/builtins2.c src/utils.c src/utils_builtins.c src/ft_split.c src/quote.c src/ft_strjoin.c src/exec.c src/redirection/simple.c src/redirection/utils_redi.c src/redirection/double.c src/control.c

OBJC = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJC}
	${CC} ${CFLAGS} ${OBJC} -lreadline -o ${NAME}

clean: 
	 ${RM} ${OBJC}

fclean: clean
	${RM} ${NAME}

re: fclean all
