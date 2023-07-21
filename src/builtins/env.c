/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:36:48 by elisa             #+#    #+#             */
/*   Updated: 2023/07/20 15:20:18 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_minishell	g_minishell;

void	env(int fd, t_command *c)
{
	int	i;
	int	j;

	i = 0;
	if (c->option[0])
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
