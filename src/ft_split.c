/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 12:46:59 by cmichez           #+#    #+#             */
/*   Updated: 2023/07/10 22:51:17 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_size(int n)
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

char	*ft_itoa(int n)
{
	int		i;
	char	*str;
	long	nb;

	i = count_size(n);
	nb = n;
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (0);
	if (n < 0)
		nb *= -1;
	str[i--] = '\0';
	while (i >= 0)
	{
		str[i] = nb % 10 + 48;
		nb /= 10;
		i--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
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

char	**ft_split(char *str, char sep)
{
	char	**split;
	char	quote;
	int		i;
	int		n;
	int		j;

	i = 0;
	n = 0;
	quote = ' ';
	split = malloc(sizeof(char *) * (count_words(str, sep) + 1));
	if (!split)
		return (0);
	while (str[i])
	{
		while (char_is_sep(str[i], sep) && str[i] && quote == ' ')
			i++;
		j = i;
		while (str[i] && (!char_is_sep(str[i], sep) || quote != ' '))
		{
			if ((str[i] == '"' || str[i] == '\'') && str[i - 1] != '\\')
			{
				if (quote == ' ')
					quote = str[i];
				else
					quote = ' ';
			}
			i++;
		}
		if (i != j)
			split[n++] = ft_strndup(str + j, i - j);
		while (char_is_sep(str[i], sep) && str[i] && quote == ' ')
			i++;
	}
	split[n] = 0;
	return (split);
}
