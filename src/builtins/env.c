/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:36:48 by elisa             #+#    #+#             */
/*   Updated: 2023/08/02 11:33:45 by cmichez          ###   ########.fr       */
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

void	init_env(char **env)
{
	char *buf;

	buf = NULL;
	if (env[0])
	{
		g_minishell.env = copy_env(env);
		return ;
	}
	g_minishell.env = malloc(sizeof(char *) * 4);
	g_minishell.env[0] = ft_strjoin("PWD=", getcwd(buf, 0));
	g_minishell.env[1] = ft_strdup("SHLVL=1");
	g_minishell.env[2] = ft_strjoin("_=", getcwd(buf, 0));
	g_minishell.env[2] = ft_strjoin(g_minishell.env[2], "/");
	g_minishell.env[2] = ft_strjoin(g_minishell.env[2], g_minishell.av[0]);
	free(buf);
}