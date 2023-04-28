/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:25:16 by cmichez           #+#    #+#             */
/*   Updated: 2023/04/28 12:24:26 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_redirection
{
	char	*type;
	char	*word;
	struct	s_redirection *next_redi;
}	t_redirection;

typedef struct s_command
{
	char	*cmd;
	char	**option;
	t_redirection **redi;
}	t_command;

typedef struct s_minishell
{
	char **env;
	char *ligne;
	t_command *command;
}	t_minishell;

char	*readline (const char *prompt);

//parsing.c
t_command	*separate_cmd(char *cmd);
char		*var_env(char *ligne, char **env);
char		*replace_var(char *var, char **env);
char		*replace_value(char *var, char *ligne);
char		**copy_env(char **env);

//utils.c
int		ft_strcmp(char *s1, char *s2);
char	*ft_strndup(char *str, int n);
int		ft_strlen(char *str);
void	affiche(t_command *command);
int		ft_strncmp(char *s1, char *s2, size_t n);

//ft_strjoin.c
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *str);

//ft_split.c
char	**ft_split(char *str, char sep);
int		char_is_sep(char c, char sep);
int		count_words(const char *str, char sep);

//quote.c
char	**separate_quote(char *str, char sep);
int		count_words_quote(char *str, char sep);

#endif