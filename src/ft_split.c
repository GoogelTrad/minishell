/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 12:46:59 by cmichez           #+#    #+#             */
/*   Updated: 2023/04/23 21:05:28 by cmichez          ###   ########.fr       */
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