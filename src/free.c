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

void	free_env(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->env[i])
		free(minishell->env[i++]);
	free(minishell->env);
}

void	free_cmd(t_minishell *minishell)
{
	int				i;
	int				j;
	t_redirection	*tmp;
	t_redirection	*actu;

	i = 0;
	while (minishell->command[i].cmd)
	{
		j = 0;
		actu = minishell->command[i].redi;
		while (minishell->command[i].option[j])
			free(minishell->command[i].option[j++]);
		free(minishell->command[i].cmd);
		while (minishell->command[i].redi->there)
		{
			tmp = actu;
			actu = actu->next_redi;
			free(tmp->type);
			free(tmp->word);
		}
		free(minishell->command[i].redi);
		i++;
	}
	free(minishell->command);
}

void	free_all(t_minishell *minishell)
{
	free_env(minishell);
	free_cmd(minishell);
}
