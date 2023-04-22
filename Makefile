NAME = minishell
CFLAGS = -Wall -Wextra -Werror
CC = gcc
RM = rm -f

SRCS = src/main.c src/prompt.c src/parsing.c src/utils.c src/ft_split.c src/quote.c

OBJC = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJC}
	${CC} ${CFLAGS} ${OBJC} -lreadline -o ${NAME}

clean: 
	 ${RM} ${OBJC}

fclean: clean
	${RM} ${NAME}

re: fclean all
