/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:53:05 by cmichez           #+#    #+#             */
/*   Updated: 2023/04/22 22:23:19 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*char	**simple_quote(char *str, int *i, int *n, char **split)
{
	return (split);
}*/

char	**double_quote(char *str, int *i, int *n, char **split)
{
	int	j;

	j = *i;
	(*i)++;
	while(str[*i] && str[*i] != '"')
		(*i)++;
	split[(*n)++] = ft_strndup(str + j, *i - j);
	return (split);
}