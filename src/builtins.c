/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:32:33 by elisa             #+#    #+#             */
/*   Updated: 2023/07/10 17:30:13 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell g_minishell;

void	echo(int fd, t_command *c)
{
	int	i;
	int j;
	int	new_line;

	new_line = 0;
	if (c->option[0] && c->option[0][0] == '-' && check_option_echo(c->option[0] + 1))
		new_line = 1;
	i = 0 + new_line;
	while (c->option[i])
	{
		j = 0;
		while (c->option[i][j])
			write(fd, &c->option[i][j++], 1);
		if (c->option[i + 1] != NULL)
			write(fd, " ", 1);
		i++;
	}
	if (c->option[0] == NULL || !(c->option[0][0] == '-' && c->option[0][1] == 'n'))
		write(fd, "\n", 1);
}

void	pwd(int fd)
{
	char	*result;
	int i;

	i = 0;
	result = var_env("$PWD", 0);
	if (result != NULL)
	{
		while (result[i])
			write(fd, &result[i++], 1);
	}
	write(fd, "\n", 1);
}

void unset(t_command *c)
{
	int i;

	i = 0;
	if (var_env(c->option[0], 0))
	{
		while(g_minishell.env[i] && ft_strncmp(c->option[0], g_minishell.env[i], ft_strlen(c->option[0])) != 0)
			i++;
		if (g_minishell.env[i])
			free(g_minishell.env[i]);
		while (g_minishell.env[i])
		{
			g_minishell.env[i] = g_minishell.env[i + 1];
			i++;
		}
	}	
}
