/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:51:29 by elisa             #+#    #+#             */
/*   Updated: 2023/05/20 17:00:42 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell g_minishell;

void	ft_exit(void)
{
	if (g_minishell.command->option[0])
	{
		if (!ft_isalnum(g_minishell.command->option[0]))
		{
			ft_putstr("exit\n");
			printf("exit: %s: numeric argument required\n", g_minishell.command->option[0]);
			exit(1);
		}
		else
			g_minishell.status = ft_atoi(g_minishell.command->option[0]);
	}
	ft_putstr("exit\n");
	exit(0);
}

void	env(void)
{
	int	i;

	i = 0;
	if (g_minishell.command->option[0])
		ft_putstr("No such file or directory\n");
	else
	{
		while (g_minishell.env[i])
		{
			printf("%s\n", g_minishell.env[i]);
			i++;
		}
	}
}
