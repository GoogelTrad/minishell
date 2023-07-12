NAME = minishell
CFLAGS = -Wall -Wextra -Werror
CC = gcc
RM = rm -f
COMPIL_42 = libreadline.a
COMPIL_CELIAN = -L/opt/homebrew/Cellar/readline/8.2.1/lib/

SRCS =  src/main.c \
		src/free.c \
		src/parsing.c \
		src/builtins.c \
		src/builtins2.c \
		src/utils.c \
		src/utils_builtins.c \
		src/ft_split.c \
		src/quote.c \
		src/ft_strjoin.c \
		src/exec.c \
		src/redirection/simple.c \
		src/redirection/utils_redi.c \
		src/redirection/double.c \
		src/cd.c \
		src/utils_parsing.c \
		

OBJC = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJC}
	${CC} ${CFLAGS} ${OBJC} ${COMPIL_CELIAN} -lreadline -lncurses -o ${NAME}

clean: 
	 ${RM} ${OBJC}

fclean: clean
	${RM} ${NAME}

re: fclean all
