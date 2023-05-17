/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:51:29 by elisa             #+#    #+#             */
/*   Updated: 2023/05/17 13:10:38 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell g_minishell;

void	ft_exit(void)
{
	int	status;
	
	status = 0;
	if (g_minishell.command->option[1])
	{
		if (!ft_isalnum())
		{
			ft_putstr("exit\n");
			printf("exit: %s: numeric argument required\n");
			exit(1);
		}
		else
			status = ft_atoi(g_minishell.command->option[1]);
	}
	ft_putstr("exit\n");
	exit(0);
}
