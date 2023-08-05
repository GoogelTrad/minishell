/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:36:39 by elisa             #+#    #+#             */
/*   Updated: 2023/08/03 16:34:49 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_command *c, t_minishell *minishell)
{
	if (c->option[0])
	{
		if (!ft_isalnum(c->option[0]))
		{
			ft_putstr("exit\n");
			printf("exit: %s: numeric argument required\n", c->option[0]);
			free_all(minishell);
			minishell->status = 42;
			exit(minishell->status);
		}
		else
			minishell->status = ft_atoi(c->option[0]);
	}
	ft_putstr("exit\n");
	free_all(minishell);
	exit(minishell->status);
}
