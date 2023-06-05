/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:51:29 by elisa             #+#    #+#             */
/*   Updated: 2023/06/05 23:25:59 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell g_minishell;

void	ft_exit(void)
{
	if (g_minishell.command[g_minishell.num].option[0])
	{
		if (!ft_isalnum(g_minishell.command[g_minishell.num].option[0]))
		{
			ft_putstr("exit\n");
			printf("exit: %s: numeric argument required\n", g_minishell.command[g_minishell.num].option[0]);
			free_all();
			exit(1);
		}
		else
			g_minishell.status = ft_atoi(g_minishell.command[g_minishell.num].option[0 ]);
	}
	ft_putstr("exit\n");
	free_all();
	exit(0); 
}

void	env(int fd)
{
	int	i;
	int j;

	i = 0;
	if (g_minishell.command[g_minishell.num].option[0])
		ft_putstr("No such file or directory\n");
	else
	{
		while (g_minishell.env[i])
		{
			j = 0;
			while (g_minishell.env[i][j])
				write(fd, &g_minishell.env[i][j++], 1);
			write(g_minishell.fd, "\n", 1);
			i++;
		}
	}
}
