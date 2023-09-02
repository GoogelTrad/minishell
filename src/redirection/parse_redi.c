/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 18:09:30 by cmichez           #+#    #+#             */
/*   Updated: 2023/09/02 23:08:41 by cmichez          ###   ########.fr       */
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
		if (ligne[i] == '\\' || ligne[i] == ';')
			replace_char(ligne, i);
		if (ligne[i] == '"' || ligne[i] == '\'')
		{
			quote = ligne[i++];
			while (ligne[i] != quote && ligne[i])
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

int	verif_line(char *line)
{
	int	i;

	i = 0;
	if (line[0] == '|')
	{
		end_pipe("|");
		return (0);
	}
	while (line[i])
		i++;
	if (line[i - 1] == '|')
	{
		end_pipe("newline");
		return (0);
	}
	return (1);
}

int	verif_redi(char *word)
{
	if (word[0] == '\0')
	{
		write(2, "syntax error near unexpected token 'newline'\n", 45);
		g_status = 2;
		return (0);
	}
	return (1);
}
