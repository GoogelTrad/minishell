/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:44:47 by cmichez           #+#    #+#             */
/*   Updated: 2023/08/22 11:47:18 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i] && n > 0)
	{
		i++;
		n--;
	}
	if (n == 0)
		return (0);
	return (s1[i] - s2[i]);
}

int	ft_strcmp(char *s1, char *s2)
{
	int				i;
	unsigned char	*c;
	unsigned char	*f;

	i = 0;
	c = (unsigned char *) s1;
	f = (unsigned char *) s2;
	while (c[i] && c[i] == f[i])
		i++;
	return (c[i] - f[i]);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	get_sigint_cmd(int signal)
{
	(void)signal;
	g_status = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	str = s;
	i = 0;
	if (n)
	{
		while (i < n)
		{
			str[i] = '\0';
			i++;
		}
	}
}
