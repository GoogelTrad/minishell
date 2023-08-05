NAME = minishell
CFLAGS = -Wall -Wextra -Werror
CC = gcc
RM = rm -f
COMPIL_42 = libreadline.a
COMPIL_CELIAN = -L/opt/homebrew/Cellar/readline/8.2.1/lib/

SRCS =  src/main.c \
		src/free.c \
		src/parsing.c \
		src/utils_parsing.c \
		src/utils.c \
		src/builtins/utils_builtins.c \
		src/ft_split.c \
		src/quote.c \
		src/ft_strjoin.c \
		src/exec.c \
		src/redirection/simple.c \
		src/redirection/utils_redi.c \
		src/redirection/double.c \
		src/builtins/cd.c \
		src/builtins/env.c \
		src/builtins/echo.c \
		src/builtins/pwd.c \
		src/builtins/exit.c \
		src/builtins/unset.c \
		src/builtins/export.c \
		src/builtins/builtins.c \
		src/builtins/utils_export.c \
		src/utils_exec.c \
		

OBJC = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJC}
	${CC} ${CFLAGS} ${OBJC} ${COMPIL_CELIAN} -lreadline -lncurses -o ${NAME}

clean: 
	 ${RM} ${OBJC}

fclean: clean
	${RM} ${NAME}

re: fclean all
