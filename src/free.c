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
	while(tmp)
	{
		actu = tmp;
		tmp = tmp->next_redi;
		free(actu->type);
		free(actu->word);
		free(actu);
	}
	free(c->redi);
}

void	free_cmd(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->command[i].cmd)
	{
		if (minishell->command->redi->there)
			free_redi(minishell->command);
		if (minishell->command->option[0])
			free_double_tab(minishell->command->option);
		if (minishell->command->cmd)
			free(minishell->command->cmd);
		i++;
	}
	free(minishell->command);
	free(minishell->ligne);
	free_double_tab(minishell->av);
}

void	free_all(t_minishell *minishell)
{
	free_double_tab(minishell->env);
	free_cmd(minishell);
}
