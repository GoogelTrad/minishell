/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:44:47 by cmichez           #+#    #+#             */
/*   Updated: 2023/04/27 13:14:34 by cmichez          ###   ########.fr       */
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

void affiche(t_command *command)
{
	int	i;
	int	j;

	i = 0;
	while (command[i].cmd)
	{
		j = 0;
		printf("cmd = %s ", command[i].cmd);
		printf("option = ");
		while(command[i].option[j])
			printf("%s ", command[i].option[j++]);
		printf("\n");
		i++;
	}
}