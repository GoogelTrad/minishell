/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 22:10:07 by cmichez           #+#    #+#             */
/*   Updated: 2023/08/27 22:10:07 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *delete_char(char *ligne, int i)
{
	while (ligne[i])
	{
		ligne[i] = ligne[i + 1];
		i++;
	}
    return (ligne);
}

char *get_redi(char *ligne)
{
	if (!ft_strncmp(">>", ligne, 2))
		return (ft_strndup(ligne, 2));
	if (!ft_strncmp("<<", ligne, 2))
		return (ft_strndup(ligne, 2));
	if (ligne[0] == '>')
		return (ft_strndup(ligne, 1));
	if (ligne[0] == '<')
		return (ft_strndup(ligne, 1));
    return (NULL);
}

t_redirection	*redi_parse(char *ligne, int i, t_redirection *redis)
{
	int	j;
	int	n;

	redis->type = get_redi(ligne + i);
	n = i;
	while (ligne[i] && ligne[i] != ' ')
		i++;		
	while (ligne[i] && ligne[i] == ' ')
		i++;
	j = i;
	while (ligne[j] && ligne[j] != ' ')
		j++;
	redis->word = ft_strndup(ligne + i, j - i);
	redis->there = 1;
	while (n < j--)
		ligne = delete_char(ligne, n);
	return (redis);
}