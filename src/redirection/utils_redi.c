/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:08:50 by cmichez           #+#    #+#             */
/*   Updated: 2023/06/11 01:18:04 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_minishell g_minishell;

void parse_redi(char **ligne, t_command *c)
{
	int j;
	int n;
	char *str;

	j = 0;
	n = 0;
	while (ligne[n] && ligne[n][0] != '<' && ligne[n][0] != '>')
		n++;
	c->option = malloc(sizeof(char *) + (n + 1));
	while(ligne[j] && j < n)
	{
		str = ft_strndup(ligne[j], ft_strlen(ligne[j]));
		c->option[j] = str;
		j++;
	}
	c->option[j] = NULL;
	while (ligne[n])
	{
		if(ligne[n][0] == '<' || ligne[n][0] == '>')
		{
			str = ft_strndup(ligne[n], ft_strlen(ligne[n]));
			c->redi->type = str;
			c->redi->there = 1;
		}
		else
		{
			str = ft_strndup(ligne[n], ft_strlen(ligne[n]));
			c->redi->word = str;
		}
		n++;
	}
}