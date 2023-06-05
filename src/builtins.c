/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:32:33 by elisa             #+#    #+#             */
/*   Updated: 2023/06/05 23:23:21 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell g_minishell;

void	echo(int fd)
{
	int	i;
	int j;
	int	new_line;

	new_line = 0;	
	if (g_minishell.command[g_minishell.num].option[0] && g_minishell.command[g_minishell.num].option[0][0] == '-'
		&& check_option_echo(g_minishell.command[g_minishell.num].option[0] + 1))
		new_line = 1;
	i = 0 + new_line;
	while (g_minishell.command[g_minishell.num].option[i])
	{
		j = 0;
		while (g_minishell.command[g_minishell.num].option[i][j])
			write(fd, &g_minishell.command[g_minishell.num].option[i][j++], 1);
		if (g_minishell.command[g_minishell.num].option[i + 1] != NULL)
			write(fd, " ", 1);
		i++;
	}
	if (g_minishell.command[g_minishell.num].option[0] == NULL || !(g_minishell.command[g_minishell.num].option[0][0] == '-' && g_minishell.command[g_minishell.num].option[0][1] == 'n'))
		write(fd, "\n", 1);
}

void	pwd(int fd)
{
	char	*result;
	int i;

	i = 0;
	result = var_env("$PWD", g_minishell.env);
	if (result != NULL)
	{
		while (result[i])
			write(fd, &result[i++], 1);
	}
	write(fd, "\n", 1);
}

