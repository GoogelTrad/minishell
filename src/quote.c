/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:53:05 by cmichez           #+#    #+#             */
/*   Updated: 2023/06/12 20:14:55 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_words_quote(char *str, char sep)
{
	int	i;
	char quote;
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
		{
			if (str[i] == '"' || str[i] == '\'')
			{
				quote = str[i];
				i++;
				while (str[i] && str[i] != quote)
					i++;
				i++;
			}
			else
				i++;
		}
	}
	return (nb);
}

char	**separate_quote(char *str, char sep)
{
	char **res;
	char quote;
	int	i;
	int limite[2];
	int	j;
	int n;

	i = 0;
	n = 0;
	res = malloc(sizeof(char *) * (count_words_quote(str, sep) + 1));
	while(str[i])
	{
		while(str[i] && char_is_sep(str[i], sep))
			i++;
		j = i;
		while (!char_is_sep(str[i], sep) && str[i])
		{
			if ((str[i] == '"' || str[i] == '\'') && str[i - 1] != '\\')
			{
				limite[0] = i;
				quote = str[i];
				i++;
				while (str[i] && str[i] != quote && str[i - 1] != '\\')
					i++;
				i++;
				limite[1] = i;
				str = replace(str, limite[0], limite[1], quote);
			}
			else	
				i++;
		}
		res[n++] = ft_strndup(str + j, i - j);
		while (char_is_sep(str[i], sep) && str[i])
			i++;
	}
	res[n] = 0;
	return (res);
}

char *replace(char *str, int start, int end, char quote)
{
	int i;
	int n;
	
	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] == quote)
			n++;
		i++;		
	}
	while (str[start] && start < end && n % 2 == 0)
	{
		i = start;
		if (str[start] == quote)
		{
			while (str[i])
			{
				str[i] = str[i + 1];
				i++;
			}
		}
		start++;		
	}
	return (str);
}