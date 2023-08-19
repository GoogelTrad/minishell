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
	free(c->redi->next_redi);
	free(c->redi);
}

void	free_cmd(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->command[i].cmd)
	{
		if (minishell->command[i].redi->there)
			free_redi(&minishell->command[i]);
		if (minishell->command[i].option[0])
			free_double_tab(minishell->command[i].option);
		if (minishell->command[i].cmd)
			free(minishell->command[i].cmd);
		i++;
	}
	free(minishell->ligne);
	
}

void	free_all(t_minishell *minishell)
{
	free_double_tab(minishell->env);
	//free_double_tab(minishell->fusion);
	free_double_tab(minishell->av);
}
