/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:44:47 by cmichez           #+#    #+#             */
/*   Updated: 2023/04/26 19:10:06 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void affiche(t_command **command)
{
	t_command	**temp;
	int			i;
	int			j;

	temp = command;
	i = 0;
	while (temp[i])
	{
		j = 0;
		printf("cmd = %s ", temp[i]->cmd);
		printf("option = ");
		while (temp[j]->option[j])
		{
			printf("%s ", temp[j]->option[j]);
			j++;
		}
		printf("\n");
		i++;
	}
}