/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 18:09:30 by cmichez           #+#    #+#             */
/*   Updated: 2023/08/06 18:31:39 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redi(t_command *c, char **ligne, int i)
{
	t_redirection	*tmp;

	tmp = c->redi;
	while (ligne[i])
	{
		c->redi->type = ft_strdup(ligne[i]);
		c->redi->there = 1;
		i++;
		if (ligne[i])
		{
			c->redi->word = ft_strdup(ligne[i]);
			if (ligne[i + 1])
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

void	parse_redi(char **ligne, t_command *c)
{
	int	i;

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
	redi(c, ligne, i);
}
