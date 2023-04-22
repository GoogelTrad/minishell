/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 12:46:59 by cmichez           #+#    #+#             */
/*   Updated: 2023/04/22 17:53:56 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**isquote(char *str, char sep)
{
	char	**split;
	int		i;
	int		quote;

	split = malloc(sizeof(char *) * (count_words(str, sep) + 1));
	i = 0;
	while (str[i])
	{
		if (str[i] == 47)
			quote = 1;
		else if (str[i] == '"')
			quote = 2;
		else
			quote = 0;
		i++;
	}
	return (split);
}

char **which_split(char **split, char *str, char sep, int quote)
{
	if (quote == 0)
		split = ft_split(str, sep);
	else if (quote == 1)
		split = ft_split_dq(str, sep);
	else if (quote == 2)
		split = ft_split_dq(str, sep);
	return (split);
}

char	**ft_split(char *str, char sep)
{
	char	**split;
	int		i;
	int		n;
	int		j;

	i = 0;
	n = 0;
	split = malloc(sizeof(char *) * (count_words(str, sep) + 1));
	if (!split)
		return (0);
	while (str[i])
	{
		while (char_is_sep(str[i], sep) && str[i])
			i++;
		j = i;
		while (str[i] && !(char_is_sep(str[i], sep)))
			i++;
		if (i != j)
			split[n++] = ft_strndup(str + j, i - j);
		while (char_is_sep(str[i], sep) && str[i])
			i++;
	}
	split[n] = 0;
	return (split);
}
