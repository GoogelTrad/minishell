/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epraduro <epraduro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:51:29 by elisa             #+#    #+#             */
/*   Updated: 2023/07/10 17:04:34 by epraduro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	export(t_command *c)
{
	int	i;
	int	j;

	i = 0;
	if (!c->option[0])
	{
		while (g_minishell.env[i])
		{
			j = 0;
			write(c->fd_out, "declare -x ", 11);
			while (g_minishell.env[i][j])
			{
				if (g_minishell.env[i][j] == '=')
				{
					write(c->fd_out, &g_minishell.env[i][j], 1);
					j++;
					write(c->fd_out, "\"", 1);
				}
				write(c->fd_out, &g_minishell.env[i][j], 1);
				j++;
			}
			write(1, "\"", 1);
			write(g_minishell.fd, "\n", 1);
			i++;
		}
	}
}
