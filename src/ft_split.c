/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 12:46:59 by cmichez           #+#    #+#             */
/*   Updated: 2023/08/02 21:06:38 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_size(int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n / 10)
	{
		i++;
		n /= 10;
	}
	return (i + 1);
}

int	char_is_sep(char c, char sep)
{
	if (c == sep)
		return (1);
	return (0);
}

int	count_words(const char *str, char sep)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		while (char_is_sep(str[i], sep))
			i++;
		if (!(char_is_sep(str[i], sep)) && str[i])
			nb++;
		while (!(char_is_sep(str[i], sep)) && str[i])
			i++;
	}
	return (nb);
}

char	quote_split(char *str, int i, char quote)
{
	if ((str[i] == '"' || str[i] == '\'') && str[i - 1] != '\\')
	{
		if (quote == ' ')
			quote = str[i];
		else
			quote = ' ';
	}
	return (quote);
}

char	**ft_split(char *str, char sep, int i)
{
	char	**split;
	char	quote;
	int		n;
	int		j;

	n = 0;
	quote = ' ';
	split = malloc(sizeof(char *) * (count_words(str, sep) + 1));
	if (!split)
		return (0);
	while (str[i])
	{
		char_split(str, &i, sep, quote);
		j = i;
		while (str[i] && (!char_is_sep(str[i], sep) || quote != ' '))
		{
			quote = quote_split(str, i, quote);
			i++;
		}
		if (i != j)
			split[n++] = ft_strndup(str + j, i - j);
		char_split(str, &i, sep, quote);
	}
	split[n] = 0;
	return (split);
}
