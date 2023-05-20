/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:08:50 by cmichez           #+#    #+#             */
/*   Updated: 2023/05/20 16:18:17 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_minishell g_minishell;

void parse_redi(char **ligne)
{
	int j;
	int n;
	char *str;

	j = 0;
	n = 0;
	while (ligne[n] && ligne[n][0] != '<' && ligne[n][0] != '>')
		n++;
	g_minishell.command->option = malloc(sizeof(char *) + (n + 1));
	while(j < n)
	{
		str = ft_strndup(ligne[j], ft_strlen(ligne[j]));
		g_minishell.command->option[j] = str;
		j++;
	}
	while (ligne[n])
	{
		g_minishell.command->redi = malloc(sizeof(t_redirection));
		if(ligne[n][0] == '<' || ligne[n][0] == '>')
		{
			str = ft_strndup(ligne[n], ft_strlen(ligne[n]));
			printf("str = %s\n", str);
			g_minishell.command->redi->type = str;
		}
		else
		{
			str = ft_strndup(ligne[n], ft_strlen(ligne[n]));
			g_minishell.command->redi->word = str;
		}
		n++;
	}
	//affiche(g_minishell.command);
}