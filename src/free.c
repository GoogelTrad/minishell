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

extern t_minishell	g_minishell;

void	free_env(void)
{
	int	i;

	i = 0;
	while (g_minishell.env[i])
		free(g_minishell.env[i++]);
	free(g_minishell.env);
	i = 0;
	if (g_minishell.fusion)
	{
		while (g_minishell.fusion[i])
			free(g_minishell.fusion[i++]);
		free(g_minishell.fusion);
	}
}

void	free_cmd(void)
{
	int				i;
	int				j;
	t_redirection	*tmp;
	t_redirection	*actu;

	i = 0;
	while (g_minishell.command[i].cmd)
	{
		j = 0;
		actu = g_minishell.command[i].redi;
		while (g_minishell.command[i].option[j])
			free(g_minishell.command[i].option[j++]);
		free(g_minishell.command[i].cmd);
		while (g_minishell.command[i].redi->there)
		{
			tmp = actu;
			actu = actu->next_redi;
			free(tmp->type);
			free(tmp->word);
		}
		free(g_minishell.command[i].redi);
		i++;
	}
	free(g_minishell.command);
}

void	free_all(void)
{
	free_env();
	free_cmd();
}

void check_error(int error)
{
	if (error < 0)
		perror("");
}