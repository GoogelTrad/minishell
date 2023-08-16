NAME = minishell
CFLAGS = -Wall -Wextra -Werror
CC = gcc
RM = rm -f
COMPIL_42 = libreadline.a
COMPIL_CELIAN = -L/opt/homebrew/Cellar/readline/8.2.1/lib/

SRCS =  src/builtins/cd.c \
		src/builtins/echo.c \
		src/builtins/env.c \
		src/builtins/exit.c \
		src/builtins/export.c \
		src/builtins/pwd.c \
		src/builtins/unset.c \
		src/builtins/utils_builtins.c \
		src/builtins/utils_builtins2.c \
		src/builtins/utils_export.c \
		src/builtins/utils_export2.c \
		src/redirection/double.c \
		src/redirection/parse_redi.c \
		src/redirection/simple.c \
		src/redirection/utils_redi.c \
		src/exec.c \
		src/free.c \
		src/ft_split.c \
		src/ft_strjoin.c \
		src/main.c \
		src/parsing.c \
		src/quote.c \
		src/utils_exec.c \
		src/utils_parsing.c \
		src/utils.c \


OBJC = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJC}
	${CC} ${CFLAGS} ${OBJC} ${COMPIL_CELIAN} -lreadline -lncurses -o ${NAME}

clean: 
	 ${RM} ${OBJC}

fclean: clean
	${RM} ${NAME}

re: fclean all
