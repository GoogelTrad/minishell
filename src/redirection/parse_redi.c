/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 18:09:30 by cmichez           #+#    #+#             */
/*   Updated: 2023/08/28 21:09:46 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redirection	*redi(char *ligne)
{
	t_redirection *redis;
	int i;
	int j;
	int n;

	i = 0;
	redis = malloc(sizeof(t_redirection));
	redis->there = 0;
	while (ligne[i] && ligne[i] != '>' && ligne[i] != '<')
		i++;
	if (ligne[i])
	{
		redis->type = get_redi(ligne + i);
		n = i;
		while (ligne[i] && ligne[i] != ' ')
			i++;		
		while (ligne[i] && ligne[i] == ' ')
			i++;
		j = i;
		while (ligne[j] && ligne[j] != ' ')
			j++;
		redis->word = ft_strndup(ligne + i, j - i);
		redis->there = 1;
		while (n < j--)
			ligne = delete_char(ligne, n);
		redis->next_redi = redi(ligne);
	}
	return redis;
}

void	parse_redi(char **ligne, t_command *c)
{
	int i;

	i = 1;
	if (ligne[0])
		init_cmd(c, ligne[0]);
	else
		c->cmd = NULL;
	while (ligne[i])
		i++;
	c->option = malloc(sizeof(char *) * i);
	i = 1;
	while(ligne[i] && ligne[i - 1])
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
