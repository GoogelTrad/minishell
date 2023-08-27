/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 19:16:44 by cmichez           #+#    #+#             */
/*   Updated: 2023/04/19 19:17:16 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redi(t_command *c)
{
	t_redirection	*tmp;
	t_redirection	*actu;

	tmp = c->redi;
	while (tmp)
	{
		printf("coucou\n");
		actu = tmp;
		printf("coucou2\n");
		tmp = tmp->next_redi;
		printf("coucou3\n");
		if (actu->type)
		{
			printf("coucou free\n");
			free(actu->type);
		}
		printf("coucou4\n");
		if (actu->word)
			free(actu->word);
		printf("coucou5\n");
		free(actu);
	}
}

void	free_cmd(t_minishell *minishell)
{
	int	i;

	i = 0;
	if (minishell->command)
	{
		while (minishell->command[i].cmd)
		{
			free_redi(&minishell->command[i]);
			free_double_tab(minishell->command[i].option);
			free(minishell->command[i].cmd);
			i++;
		}
		free(minishell->command);
	}
	free(minishell->ligne);
}

void	free_all(t_minishell *minishell)
{
	free_double_tab(minishell->env);
	free_double_tab(minishell->av);
}
