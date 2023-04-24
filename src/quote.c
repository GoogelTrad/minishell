/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:53:05 by cmichez           #+#    #+#             */
/*   Updated: 2023/04/24 15:25:01 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*char	**simple_quote(char *str, int *i, int *n, char **split)
{
	return (split);
}*/

int count_words_quote(char *str, char quote, char sep)
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

void	double_quote(char *str, char **split, char sep)
{
	char **res;
	int	i;
	int	j;

	i = 0;
	res = malloc(sizeof(char *) * (count_words_quote(str, '"', sep)));
	while(str[i])
	{
		while(str[i] && char_is_sep(str[i], sep))
			i++;
		if(str[i] == '"')
		{
			j = i++;
			while(str[i] && str[i] == '"')
				i++;
		}
	}
}