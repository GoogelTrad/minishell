/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:53:05 by cmichez           #+#    #+#             */
/*   Updated: 2023/04/22 17:55:37 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_sq(char *str, char sep)
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
		if (str[i] == 47)
		{
			i++;
			while (str[i] != 47)
				i++;
		}
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

char	**ft_split_dq(char *str, char sep)
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
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"')
				i++;
		}
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