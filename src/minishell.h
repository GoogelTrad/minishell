/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:25:16 by cmichez           #+#    #+#             */
/*   Updated: 2023/07/10 17:42:21 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>

typedef struct s_redirection
{
	char	*type;
	char	*word;
	int		there;
	struct	s_redirection *next_redi;
}	t_redirection;

typedef struct s_command
{
	int		fd_in;
	int		fd_out;
	char	*cmd;
	char	**option;
	t_redirection *redi;
}	t_command;

typedef struct s_minishell
{
	int status;
	int ac;
	char *ligne;
	char **env;
	char **fusion;
	char **av;
	int fd;
	t_command *command;
}	t_minishell;

char		*readline (const char *prompt);
void    	rl_replace_line(const char *text, int clear_undo);

//parsing.c
void		separate_cmd(char *ligne);
char		*var_env(char *ligne, int j);
char		*replace_var(char *var, char **env);
char		*replace_value(char *var, char *ligne, int i);
char		**copy_env(char **env);

//utils_parsing.c
char		choose_quote(char c, char quote);
char		*write_var(char *ligne, char *var, char *replace, int i, int j);
int			while_env(char *ligne, int i[2], char *replace, char *var, char quote);
void		treat_env(int i[2], char **ligne);

//utils.c
int			ft_strcmp(char *s1, char *s2);
char		*ft_strndup(char *str, int n);
int			ft_strlen(char *str);
void		affiche(t_command *c);
int			ft_strncmp(char *s1, char *s2, size_t n);
void		ft_bzero(void *s, size_t n);

//utils_builtins.c
int			check_option_echo(char	*str);
void		ft_putstr(char *s);
int			ft_isalnum(char *str);
int			ft_atoi(const char *str);

//ft_strjoin.c
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strdup(char *str);
int			isCharAlnum(char c);
int			ft_isdigit(int c);

//ft_split.c
char		**ft_split(char *str, char sep);
int			char_is_sep(char c, char sep);
int			count_words(const char *str, char sep);
char		*ft_itoa(int n);

//quote.c
char		**separate_quote(char *str, char sep);
int			count_words_quote(char *str, char sep);
char		*dolar_dolar(void);

//builtins.c
void		echo(int fd, t_command *c);
void		pwd(int fd);
void		unset(t_command *c);

//builtins2.c
void		ft_exit(t_command *c);
void		env(int fd, t_command *c);
void 		export(t_command *c);


//utils_redi.c
void		parse_redi(char **ligne, t_command *c);
char		**display_quote(char **str);
char		*replace(char *str, int start, int end);

//simple.c
void		simple_droite(t_command *c);
void		simple_gauche(t_command *c);

//double.c
void		double_droite(t_command *c);
void		double_gauche(t_command *c);
int			check_env(char *ligne);
char		*coucou(char *ligne);
void		double_read(t_command *c);

//exec.c
void		belle_exec(t_command *c);
void		exec(int fd, t_command *c);
void		fusion_exec(t_command *c);
void		exec_redi(t_command *c);
void		exec_others(t_command *c);
void		exec_fork(char *fichier, t_command *c);

//free.c
void		free_all();

//cd.c
void		cd(t_command *c);
void		change_pwd(char *path);

//main.c
void		get_sigint(int signal);
void		bworded(t_command *c);
void		blocksig(int signal);
char 		*var_arg(char **av, char *ligne, int ac);

#endif