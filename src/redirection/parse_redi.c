/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 18:09:30 by cmichez           #+#    #+#             */
/*   Updated: 2023/08/26 23:29:11 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redirection	*redi(char *ligne, int i)
{
	t_redirection *redi;

	redi = NULL;
	while (ligne[i] && ligne[i] != '>' && ligne[i] != '<')
		i++;
	if (ligne[i])
	{
		redi->type = get_redi(ligne + i);
		while (ligne[i] && ligne[i] == ' ')
			i++;
		redi = malloc(sizeof(t_redirection));
		int j = 0;
		while (ligne[j] && ligne[j] != ' ')
			j++;
		redi->word = ft_strndup(ligne[i], j - i);
		redi->there = 1;
		while (i--)
			ligne = delete_char(ligne);
		redi->next_redi = redi(ligne, i);
	}
	return redi;
}

char *delete_char(char *ligne)
{
	int i = 0;
	
	while (ligne[i])
	{
		ligne[i] = ligne[i + 1];
		i++;
	}
}

char *get_redi(char *ligne)
{
	if (!ft_strncmp(">>", ligne, 2))
		return (ft_strndup(ligne, 2));
	if (!ft_strncmp("<<", ligne, 2))
		return (ft_strndup(ligne, 2));
	if (ligne[0] == '>')
		return (ft_strndup(ligne, 1));
	if (ligne[0] == '<')
		return (ft_strndup(ligne, 1));
		
}

void	parse_redi(char *ligne, t_command *c)
{
	int	i;

	i = 0;
	c->redi = redi(ligne, i);
	while (ligne[i] && ligne[i] != '>' && ligne[i] != '<')
		i++;
	c->option = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (ligne[i] && ligne[i] != '>' && ligne[i] != '<')
	{
		c->option[i] = ft_strdup(ligne[i]);
		i++;
	}
	c->option[i] = NULL;
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
