/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epraduro <epraduro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:51:29 by elisa             #+#    #+#             */
/*   Updated: 2023/07/05 18:00:46 by epraduro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell g_minishell;

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
	int j;

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

void export(int fd, t_command *c)
{
	int i = 0;
	int j;

	if (!c->option[0])
	{
		while (g_minishell.env[i])
		{
			j = 0;
			write(g_minishell.fd, "declare -x ", 11);
			while (g_minishell.env[i][j])
			{
				if (g_minishell.env[i][j] == '=')
				{
					write(fd, &g_minishell.env[i][j], 1);
					j++;
					write(fd, "\"", 1);	
				}
				write(fd, &g_minishell.env[i][j], 1);
				j++;
			}
			write(1, "\"", 1);
			write(g_minishell.fd, "\n", 1);
			i++;
		}
	}
}