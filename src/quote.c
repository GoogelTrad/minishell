/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:53:05 by cmichez           #+#    #+#             */
/*   Updated: 2023/04/26 16:11:43 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*char	**simple_quote(char *str, int *i, int *n, char **split)
{
	return (split);
}*/

int count_words_quote(char *str, char sep)
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
		{
			if (str[i] == '"' || str[i] == '\'')
			{
				i++;
				while (str[i] && (str[i] != '"' || str[i] != '\''))
					i++;
				i++;
			}
			else
				i++;
		}
	}
	return (nb);
}

char	**double_quote(char *str, char sep)
{
	char **res;
	int	i;
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
			if (str[i] == '"' || str[i] == '\'')
			{
				i++;
				while (str[i] && (str[i] != '"' || str[i] != '\''))
					i++;
				i++;
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