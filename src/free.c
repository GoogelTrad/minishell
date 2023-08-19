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
		actu = tmp;
		tmp = tmp->next_redi;
		if (actu->type)
			free(actu->type);
		if (actu->word)
			free(actu->word);
		free(actu);
	}
}

void	free_cmd(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->command[i].cmd)
	{
		free_redi(&minishell->command[i]);
		free_double_tab(minishell->command[i].option);
		free(minishell->command[i].cmd);
		i++;
	}
	free(minishell->ligne);
	free(minishell->command);
}

void	free_all(t_minishell *minishell)
{
	free_double_tab(minishell->env);
	free_double_tab(minishell->av);
}
