/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:08:50 by cmichez           #+#    #+#             */
/*   Updated: 2023/05/19 15:39:49 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_minishell g_minishell;

char *parse_redi(char *ligne, t_command *command, int n)
{
	int i;
	int j;
	char *res;
	char *str;

	i = 0;
	while (ligne[i])
	{
		if (ligne[i] == '>' || ligne[i] == '<')
		{
			break ;
		}
		i++;
	}
	res = ft_strndup(ligne, i);
	j = i;
	while(ligne[j] && ligne[j] != ' ')
		j++;
	str = ft_strndup(ligne + i, j);
	command[n].redi->type = str;
	while (ligne[j] && ligne[j] == ' ')
		j++;
	i = j;
	while (ligne[i] && ligne[i] != ' ')
		i++;
	str = ft_strndup(ligne + j, i);
	command[n].redi->word = str;
	return (res);
}