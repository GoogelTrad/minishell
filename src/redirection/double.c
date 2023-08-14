/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 01:51:01 by cmichez           #+#    #+#             */
/*   Updated: 2023/05/22 01:51:01 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	double_droite(t_command *c)
{
	c->fd_out = open(c->redi->word, O_CREAT | O_RDWR | O_APPEND, 0644);
}

void	replace_heredoc(t_minishell *minishell)
{
	int		i;
	int		j;
	int		k;
	char	quote;

	i = 0;
	k = 1;
	while (minishell->ligne[i])
	{
		if (minishell->ligne[i] == '"' || minishell->ligne[i] == '\'')
		{
			j = i++;
			quote = minishell->ligne[j];
			while(minishell->ligne[i] && minishell->ligne[i] != quote)
				i++;
			if(minishell->ligne[i] == quote && i != j)
				minishell->ligne = replace(minishell->ligne, quote, &k);
		}
		i++;
	}
}

void	double_gauche(t_command *c, t_minishell *minishell)
{
	int		pipes[2];
	char	*ligne;

	pipe(pipes);
	c->fd_in = pipes[0];
	replace_heredoc(minishell);
	if (check_env(minishell->ligne))
		c->redi->word = ft_strdup(coucou(minishell->ligne));
	ligne = readline("> ");
	impr_double(c, pipes, ligne);
	while (ft_strcmp(ligne, c->redi->word) != 0)
	{
		ligne = readline("> ");
		impr_double(c, pipes, ligne);
	}
	close(pipes[1]);
}

char	*coucou(char *ligne)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	while (ligne[i])
	{
		if (ligne[i] == '$')
		{
			j = i;
			while (ligne[i] && ligne[i] != ' ' && ligne[i] != '"' &&
				ligne[i] != '\'')
				i++;
			res = ft_strndup(ligne + j, i);
			printf("res = %s\n", res);
			return (res);
		}
		i++;
	}
	return (NULL);
}

int	check_env(char *ligne)
{
	int	i;

	i = 0;
	while (ligne[i])
	{
		if (ligne[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	impr_double(t_command *c, int pipes[2], char *ligne)
{
	int	i;

	i = 0;
	if (ft_strcmp(ligne, c->redi->word) != 0)
	{
		while (ligne[i])
			write(pipes[1], &ligne[i++], 1);
		write(pipes[1], "\n", 1);
	}
}
