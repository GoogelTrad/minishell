/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:25:16 by cmichez           #+#    #+#             */
/*   Updated: 2023/08/19 16:54:56 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>
# include <string.h>

//******************************STRUCTURES******************************//

typedef struct s_redirection
{
	char					*type;
	char					*word;
	int						there;
	struct s_redirection	*next_redi;
}	t_redirection;

typedef struct s_command
{
	int				fd_in;
	int				fd_out;
	char			*word;
	char			*cmd;
	char			**option;
	t_redirection	*redi;
}	t_command;

typedef struct s_minishell
{
	int			status;
	int			ac;
	char		*ligne;
	char		**env;
	int			size_env;
	char		**fusion;
	char		**av;
	int			fd;
	int			incr;
	int			cd_n;
	int			pid;

	t_command	*command;
}	t_minishell;

//******************************FONCTIONS******************************//

char		*readline(const char *prompt);
void		rl_replace_line(const char *text, int clear_undo);

// builtins/cd.c
void		cd(t_command *c, t_minishell *minishell);
void		old_pwd(int i, t_minishell *minishell);
void		pwd_back(char *path, int i, int j, t_minishell *minishell);
void		pwd_front(char *path, int i, t_minishell *minishell);
void		change_pwd(char *path, t_minishell *minishell);

// builtins/echo.c

void		echo(int fd, t_command *c, t_minishell *minishell);

// builtins/env.c

int			len_env(char **env);
void		env(int fd, t_command *c, t_minishell *minishell);
void		init_env(char **env, t_minishell *minishell);

// builtins/exit.c

void		ft_exit(t_command *c, t_minishell *minishell);

// builtins/export.c
void		export_alone(int fd, char **tab);
int			add_var_env(char *word, char *value, t_minishell *minishell);
void		export_by_ascii(char **tab);
void		aff_export_alone(int fd, t_minishell *minishell);
void		export(t_command *c, t_minishell *minishell);

// builtins/pwd.c

void		pwd(int fd);

// builtins/unset.c
size_t		env_size(char *env);
void		ft_free(t_minishell *env);
void		ft_putchar(char c);
void		unset(t_command *c, t_minishell *minishell);

// builtins/utils_builtins.c
int			check_option_echo(char	*str);
void		ft_putstr(char *s);
int			ft_isalnum(char *str);
int			ft_atoi(const char *str);

// builtins/utils_builtins2.c
char		*verif_cd(t_command *c, t_minishell *minishell);
int			verif_arg_cd(t_command *c, t_minishell *minishell);
// builtins/utils_export.c
char		**copy_tab(char **tab);
int			ft_isalpha(int c);
void		*ft_calloc(size_t count, size_t size);
char		*get_char(char *cmd, size_t start, size_t end);
char		*set_value(char *word, char *value);

//  builtins/utils_export2.c
int 		is_valid(int c);
int			isok(t_command *c, t_minishell *minishell, int i, int k);
int			check_option_export(t_command *c, t_minishell *minishell, int i, int *k);
int			find_my_var(char *word, t_minishell *minishell);
int			change_var(char *word, char *value, int index, t_minishell *minishell);

// redirection/double.c
int			double_droite(t_command *c);
int			double_gauche(t_command *c, t_minishell *minishell);
char		*coucou(char *ligne);
int			check_env(char *ligne);
void		impr_double(t_command *c, int pipes[2], char *ligne);

// redirection/parse_redi.c

void		redi(t_command *c, char **ligne, int i);
void		parse_redi(char **ligne, t_command *c);
void		replace_heredoc(t_minishell *minishell);
int			verif_line(char *line, t_minishell *minishell);
int			verif_redi(char *word, t_minishell *minishell);

// redirection/simple.c
int			simple_droite(t_command *c, t_minishell *minishell);
int			simple_gauche(t_command *c, t_minishell *minishell);

// redirection/utils_redi.c
char		**display_quote(char **str);
char		*replace_quote(char *str, int i);
char		*replace(char *str, char quote, int *j);
char		*get_env(char *var, char **env);

//exec.c
void		belle_exec(t_command *c, t_minishell *minishell);
void		exec(int fd, t_command *c, t_minishell *minishell);
int			exec_redi(t_command *c, t_minishell *minishell);
void		exec_others(t_command *c, int verif, t_minishell *minishell);
void		exec_fork(char *fichier, t_command *c, t_minishell *minishell);

//free.c
void		free_cmd(t_minishell *minishell);
void		free_all(t_minishell *minishell);
void		free_redi(t_command *c);

//ft_split.c
int			count_size(int n);
int			char_is_sep(char c, char sep);
int			count_words(const char *str, char sep);
char		quote_split(char *str, int i, char quote);
char		**ft_split(char *str, char sep, int i);

//ft_strjoin.c
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strdup(char *str);
int			ischaralnum(char c);
int			ft_isdigit(int c);
void		bworded(t_command *c);

//main.c
int			main(int ac, char **av, char **env);
void		prompt(char *ligne, t_minishell *minishell);
void		get_sigint(int signal);
void		blocksig(int signal);
char		*var_arg(char **av, char *ligne, int ac);

//parsing.c
char		**copy_env(char **env);
int			separate_cmd(char *ligne, t_minishell *minishell);
char		*var_env(char *ligne, int j, t_minishell *minishell);
char		*replace_value(char *var, char *ligne, int i);
void		end_pipe(t_minishell *minishell);

//quote.c
int			count_words_quote(char *str, char sep);
int			while_quote(char *str, int i, char sep);
char		**separate_quote(char *str, char sep);
char		*dolar_dolar(t_minishell *minishell);

//utils_exec.c
void		no_command(int verif, t_command *c, t_minishell *minishell);
void		fusion_exec(t_command *c, t_minishell *minishell);
void		free_double_tab(char **tab);
char		*ft_itoa(int n);
void		char_split(char *str, int *i, char sep, char quote);

//utils_parsing.c
char		*ft_strndup(char *str, int n);
char		choose_quote(char c, char quote, int *i, int verif);
int			put_error(int type);
char		*replace_var_env(char *ligne, int i, int j, t_minishell *minishell);
char		*type_of_var(char *ligne, int i, int j, t_minishell *minishell);

//utils.c
int			ft_strncmp(char *s1, char *s2, size_t n);
int			ft_strcmp(char *s1, char *s2);
int			ft_strlen(char *str);
void		get_sigint_cmd(int signal);
void		ft_bzero(void *s, size_t n);

#endif