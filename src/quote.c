/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:53:05 by cmichez           #+#    #+#             */
/*   Updated: 2023/08/31 17:31:10 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words_quote(char *str, char sep)
{
	int		i;
	char	quote;
	int		nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		while (char_is_sep(str[i], sep) && str[i])
			i++;
		if (!(char_is_sep(str[i], sep)) && str[i])
			nb++;
		while (!(char_is_sep(str[i], sep)) && str[i])
		{
			if (str[i] == '"' || str[i] == '\'')
			{
				quote = str[i];
				i++;
				while (str[i] && str[i] != quote)
					i++;
			}
			i++;
		}
	}
	return (nb);
}

int	while_quote(char *str, int i, char sep)
{
	char	quote;

	while (!char_is_sep(str[i], sep) && str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && str[i - 1] != '\\')
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote && str[i - 1] != '\\')
				i++;
		}
		i++;
	}
	return (i);
}

char	**separate_quote(char *str, char sep)
{
	char	**res;
	int		i;
	int		j;
	int		n;

	i = 0;
	n = 0;
	res = malloc(sizeof(char *) * (count_words_quote(str, sep) + 1));
	while (str[i])
	{
		while (str[i] && char_is_sep(str[i], sep))
			i++;
		j = i;
		i = while_quote(str, i, sep);
		res[n++] = ft_strndup(str + j, i - j);
		while (char_is_sep(str[i], sep) && str[i])
			i++;
	}
	res[n] = 0;
	return (res);
}

char	*dolar_dolar(t_minishell *minishell)
{
	pid_t	pid;
	char	*res;

	pid = getpid();
	res = ft_itoa(pid);
	minishell->incr = 2;
	return (res);
}

void	init_cmd(t_command *c, char *ligne)
{
	c->cmd = ft_strdup(ligne);
	c->fd_in = 0;
	c->fd_out = 1;
}
