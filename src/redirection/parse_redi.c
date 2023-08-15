/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 18:09:30 by cmichez           #+#    #+#             */
/*   Updated: 2023/08/15 16:34:51 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redi(t_command *c, char **ligne, int i)
{
	t_redirection	*tmp;

	tmp = c->redi;
	while (ligne[i])
	{
		c->redi->type = ft_strdup(ligne[i]);
		c->redi->there = 1;
		i++;
		if (ligne[i])
		{
			c->redi->word = ft_strdup(ligne[i]);
			if (ligne[i + 1])
			{
				c->redi->next_redi = malloc(sizeof(t_redirection));
				c->redi = c->redi->next_redi;
				c->redi->there = 0;
			}
		}
		if (ligne[i])
			i++;
	}
	c->redi->next_redi = malloc(sizeof(t_redirection));
	c->redi->next_redi->there = 0;
	c->redi = tmp;
}

void	parse_redi(char **ligne, t_command *c)
{
	int	i;

	i = 0;
	while (ligne[i] && ligne[i][0] != '>' && ligne[i][0] != '<')
		i++;
	c->option = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (ligne[i] && ligne[i][0] != '>' && ligne[i][0] != '<')
	{
		c->option[i] = ft_strdup(ligne[i]);
		i++;
	}
	c->option[i] = NULL;
	redi(c, ligne, i);
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

int	verif_line(char *line)
{
	int	i;

	i = 0;
	while(line[i])
		i++;
	if (line[i - 1] == '|')
		return (0);
	return (1);
}

int	verif_redi(char *word, t_minishell *minishell)
{
	if (!word)
	{
		write(2, "syntax error near unexpected token 'newline'\n", 45);
		minishell->status = 1;
		return (0);
	}
	return (1);
}