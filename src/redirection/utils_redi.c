/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:08:50 by cmichez           #+#    #+#             */
/*   Updated: 2023/07/02 00:22:26 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_minishell g_minishell;

void parse_redi(char **ligne, t_command *c)
{
	int i;
	t_redirection *tmp;

	i = 0;
	while (ligne[i] && ligne[i][0] != '>' && ligne[i][0] != '<')
		i++;
	c->option = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (ligne[i] && ligne[i][0] != '>' && ligne[i][0] != '<')
	{
		c->option[i] = ft_strdup(ligne[i]);
		i++;
	}
	c->option[i] = NULL;
	tmp = c->redi;
	while (ligne [i])
	{
		c->redi->type = ft_strdup(ligne[i]);
		c->redi->there = 1;
		i++;
		if (ligne[i])
		{
			c->redi->word = ft_strdup(ligne[i]);
			if(ligne[i + 1])
			{
				c->redi->next_redi = malloc(sizeof(t_redirection));
				c->redi = c->redi->next_redi;
				c->redi->there = 0;
			}
		}
		i++;
	}
	c->redi->next_redi = malloc(sizeof(t_redirection));
	c->redi->next_redi->there = 0;
	c->redi = tmp;
}

/*
void parse_redi(char **ligne, t_command *c)
{
	int j;
	int n;
	char *str;
	t_redirection *tmp;

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
	tmp = c->redi;
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
			c->redi = c->redi->next_redi;
		}
		n++;
	}
	c->redi = tmp;
}
*/