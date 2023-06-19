/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:51:29 by elisa             #+#    #+#             */
/*   Updated: 2023/06/19 14:13:54 by cmichez          ###   ########.fr       */
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
			g_minishell.status = ft_atoi(c->option[0 ]); 
	}
	ft_putstr("exit\n");
	free_all();
	exit(0); 
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

void	cd(t_command *c)
{
	int verif;
	
	if (c->option[0])
	{
		verif = chdir(c->option[0]);
		if (verif == -1)
			printf("cd %s : No such file or directory\n", c->option[0]);
		else
			change_pwd(c->option[0]);
	}
}

void	change_pwd(char *path)
{
	int i;
	int j;
	int n;
	char *cpy;

	i = 0;
	n = 0;
	while (ft_strncmp(g_minishell.env[i], "PWD", 3) != 0)
		i++;
	j = ft_strlen(g_minishell.env[i]);
	while (g_minishell.env[i][n] != '/')
		n++;
	if (path[0] == '/')
	{	
		if (path[ft_strlen(path) - 1] == '/')
			path = ft_strndup(path, ft_strlen(path) - 1);
		g_minishell.env[i] = ft_strdup(ft_strjoin(ft_strndup(g_minishell.env[i], n), path));
	}
	else
	{
		if (path && ft_strncmp(path, "..", 2) == 0)
		{
			j--;
			while (g_minishell.env[i][j] != '/')
				j--;
			cpy = ft_strndup(g_minishell.env[i] + n, j - n);
			g_minishell.env[i] = ft_strdup(ft_strjoin(ft_strndup(g_minishell.env[i], n), cpy));
			if (path[2])
				change_pwd(path + 3);
		}
		else if (path && ft_strncmp(path, "..", 2) != 0)
		{
			g_minishell.env[i] = ft_strjoin(g_minishell.env[i], "/");
			if (path[ft_strlen(path) - 1] == '/')
				path = ft_strndup(path, ft_strlen(path) - 1);
			g_minishell.env[i] = ft_strjoin(g_minishell.env[i], path);
		}
	}
}