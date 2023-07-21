/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:36:39 by elisa             #+#    #+#             */
/*   Updated: 2023/07/20 14:53:38 by elisa            ###   ########.fr       */
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
			exit(1);
		}
		else
			g_minishell.status = ft_atoi(c->option[0]); 
	}
	ft_putstr("exit\n");
	free_all();
	exit(1); 
}
