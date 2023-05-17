/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:51:29 by elisa             #+#    #+#             */
/*   Updated: 2023/05/17 15:01:42 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell g_minishell;

void	ft_exit(void)
{
	if (g_minishell.command->option[1])
	{
		if (!ft_isalnum(g_minishell.command->option[1]))
		{
			ft_putstr("exit\n");
			printf("exit: %s: numeric argument required\n", g_minishell.command->option[1]);
			exit(1);
		}
		else
			g_minishell.status = ft_atoi(g_minishell.command->option[1]);
	}
	ft_putstr("exit\n");
	exit(0);
}
