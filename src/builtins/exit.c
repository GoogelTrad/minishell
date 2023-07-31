/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:36:39 by elisa             #+#    #+#             */
/*   Updated: 2023/07/25 14:15:31 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_minishell	g_minishell;

void	ft_exit(t_command *c)
{
	if (c->option[0])
	{
		if (!ft_isalnum(c->option[0]))
		{
			ft_putstr("exit\n");
			printf("exit: %s: numeric argument required\n", c->option[0]);
			free_all();
			g_minishell.status = 42;
			exit(g_minishell.status);
		}
		else
			g_minishell.status = ft_atoi(c->option[0]);
	}
	ft_putstr("exit\n");
	free_all();
	exit(g_minishell.status);
}
