/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:36:48 by elisa             #+#    #+#             */
/*   Updated: 2023/07/25 15:06:27 by cmichez          ###   ########.fr       */
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
	{
		g_minishell.status = 127;
		write(2, "cd: ", 4);
		write(2, c->option[0], ft_strlen(c->option[0]));
		write(2, ": ", 3);
		write(2, "No such file or directory\n", 26);
		return ;
	}
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
	g_minishell.status = 0;
}
