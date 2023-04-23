/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:53:05 by cmichez           #+#    #+#             */
/*   Updated: 2023/04/23 21:37:48 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*char	**simple_quote(char *str, int *i, int *n, char **split)
{
	return (split);
}*/

int count_words_quote(char *str, char quote, char sep)
{
	int i;
	int j;
	int in_quote;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == quote)
			in_quote = 1;
	}
}

void	double_quote(char *str, char **split, char sep)
{
	char **res;
	int	i;
	int	j;

	i = 0;
	res = malloc(sizeof(char *) * (count_words_quote(str, '"', sep)))
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