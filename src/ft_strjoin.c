/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 00:49:06 by cmichez           #+#    #+#             */
/*   Updated: 2023/04/28 00:49:06 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	int		len_s1;
	int		n;
	int		i;
	int		len_s2;

	n = 0;
	i = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	result = malloc(sizeof(char) * (len_s1 + len_s2) + 1);
	while (n < len_s1)
	{
		result[n] = s1[n];
		n++;
	}
	while (n < (len_s1 + len_s2))
		result[n++] = s2[i++];
	result[n] = 0;
	return (result);
}

char	*ft_strdup(char *str)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

int	ischaralnum(char c)
{
	if (!((48 <= c && 57 >= c) || (65 <= c && 90 >= c)
			|| (97 <= c && 122 >= c)))
		return (0);
	return (1);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

void	bworded(t_command *c)
{
	if (c->cmd && c->option[0])
	{
		if (ft_strcmp(c->cmd, "cat") == 0 && c->option[0] == NULL)
			signal(SIGQUIT, &blocksig);
	}
}
