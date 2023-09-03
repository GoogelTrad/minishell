/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:16:40 by cmichez           #+#    #+#             */
/*   Updated: 2023/09/03 16:16:53 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(char *str, int n)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i] && i < n)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

int	is_inquote(char *ligne, int max)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (i < max)
	{
		if (ligne[i] == '\'' && quote == 0)
			quote = 1;
		else if (ligne[i] == '"' && quote == 0)
			quote = 2;
		else if (ligne[i] == '"' && quote == 2)
			quote = 0;
		else if (ligne[i] == '\'' && quote == 1)
			quote = 0;
		i++;
	}
	return (quote);
}

int	put_error(int type)
{
	write(2, strerror(type), ft_strlen(strerror(type)));
	write(2, "\n", 1);
	return (type);
}
