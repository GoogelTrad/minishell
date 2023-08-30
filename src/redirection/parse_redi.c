/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 18:09:30 by cmichez           #+#    #+#             */
/*   Updated: 2023/08/30 13:02:37 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redirection	*redi(char *ligne)
{
	t_redirection	*redis;
	char			quote;
	int				i;

	i = 0;
	redis = malloc(sizeof(t_redirection));
	redis->there = 0;
	while (ligne[i] && ligne[i] != '>' && ligne[i] != '<')
	{
		if (ligne[i] == '"' || ligne[i] == '\'')
		{
			quote = ligne[i++];
			while (ligne[i] != quote)
				i++;
		}
		i++;
	}
	if (ligne[i])
	{
		redis = redi_parse(ligne, i, redis);
		redis->next_redi = redi(ligne);
	}
	return (redis);
}

void	parse_redi(char **ligne, t_command *c)
{
	int	i;

	i = 1;
	if (ligne[0])
		init_cmd(c, ligne[0]);
	else
		c->cmd = NULL;
	while (ligne[i])
		i++;
	c->option = malloc(sizeof(char *) * i);
	i = 1;
	while (ligne[i] && ligne[i - 1])
	{
		c->option[i - 1] = ft_strdup(ligne[i]);
		i++;
	}
	c->option[i - 1] = NULL;
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
			while (minishell->ligne[i] && minishell->ligne[i] != quote)
				i++;
			if (minishell->ligne[i] == quote && i != j)
				minishell->ligne = replace(minishell->ligne, quote, &k);
		}
		i++;
	}
}

int	verif_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	if (line[i - 1] == '|')
	{
		end_pipe();
		return (0);
	}
	return (1);
}

int	verif_redi(char *word)
{
	if (!word)
	{
		write(2, "syntax error near unexpected token 'newline'\n", 45);
		g_status = 1;
		return (0);
	}
	return (1);
}
