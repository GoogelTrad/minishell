/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:25:16 by cmichez           #+#    #+#             */
/*   Updated: 2023/08/03 16:40:04 by cmichez          ###   ########.fr       */
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
	char	*word;
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
	int size_env;
	char **fusion;
	char **av;
	int fd;
	
	t_command *command;
}	t_minishell;

char		*readline (const char *prompt);
void    	rl_replace_line(const char *text, int clear_undo);

//parsing.c
void		separate_cmd(char *ligne, t_minishell *minishell);
char		*var_env(char *ligne, int j, t_minishell *minishell);
char		*replace_var(char *var, char **env);
char		*replace_value(char *var, char *ligne, int i);
char		**copy_env(char **env);

//utils_parsing.c
char		choose_quote(char c, char quote);
int			put_error(int type);

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
int			ischaralnum(char c);
int			ft_isdigit(int c);
void		bworded(t_command *c);

//ft_split.c
char		**ft_split(char *str, char sep, int i);
int			char_is_sep(char c, char sep);
int			count_words(const char *str, char sep);
int			count_size(int n);
char		*ft_itoa(int n);

//quote.c
char		**separate_quote(char *str, char sep);
int			count_words_quote(char *str, char sep);
char		*dolar_dolar(void);

//builtins.c
void		echo(int fd, t_command *c, t_minishell *minishell);
void		pwd(int fd, t_minishell *minishell);
void		unset(t_command *c, t_minishell *minishell);

//builtins2.c
void		ft_exit(t_command *c, t_minishell *minishell);
void		env(int fd, t_command *c, t_minishell *minishell);

//utils_redi.c
void		parse_redi(char **ligne, t_command *c);
char		**display_quote(char **str);
char		*replace(char *str, char quote);
char		*get_env(char *var, char **env);

//simple.c
void		simple_droite(t_command *c);
void		simple_gauche(t_command *c);

//double.c
void		double_droite(t_command *c);
void		double_gauche(t_command *c, t_minishell *minishell);
int			check_env(char *ligne);
char		*coucou(char *ligne);
void		double_read(t_command *c);

//exec.c
void		belle_exec(t_command *c, t_minishell *minishell);
void		exec(int fd, t_command *c, t_minishell *minishell);
void		exec_redi(t_command *c, t_minishell *minishell);
void		exec_others(t_command *c, int verif, t_minishell *minishell);
void		exec_fork(char *fichier, t_command *c, t_minishell *minishell);

//utils_exec.c
void		free_double_tab(char **tab);
void		fusion_exec(t_command *c, t_minishell *minishell);
void		no_command(int verif, t_command *c, t_minishell *minishell);
void		char_split(char *str, int *i, char sep, char quote);

//free.c
void		free_all(t_minishell *minishell);
void		check_error(int error);

//cd.c
void		cd(t_command *c, t_minishell *minishell);
void		change_pwd(char *path, t_minishell *minishell);

//export.c

void 		export(t_command *c, t_minishell *minishell);
void		export_alone(int fd, char **tab);
void		export_by_ascii(char **tab, int size_env);


//utils_export.c

int			ft_isalpha(int c);
int			ft_valid_arg(char *str);
char		*set_value(char *word, char *value);
char		**copy_tab(char **tab);
char		*get_char(char *cmd, size_t start, size_t end);
int			add_var_env(char *word, char *value, t_minishell *minishell);
void		aff_export_alone(int fd, t_minishell *minishell);

//main.c
void		get_sigint(int signal);
void		blocksig(int signal);
char 		*var_arg(char **av, char *ligne, int ac);
void		prompt(char *ligne, t_minishell *minishell);

//env.c
void		init_env(char **env, t_minishell *minishell);
int			len_env(char **env);

#endif