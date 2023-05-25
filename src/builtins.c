/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:32:33 by elisa             #+#    #+#             */
/*   Updated: 2023/05/25 03:19:22 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell g_minishell;

void	echo(void)
{
	int	i;
	int	new_line;

	new_line = 0;	
	if (g_minishell.command[g_minishell.num].option && g_minishell.command[g_minishell.num].option[0][0] == '-'
		&& check_option_echo(g_minishell.command[g_minishell.num].option[0] + 1))
		new_line = 1;
	i = 0 + new_line;
	while (g_minishell.command[g_minishell.num].option[i])
	{
		ft_putstr(g_minishell.command[g_minishell.num].option[i]);
		if (g_minishell.command[g_minishell.num].option[i + 1] != NULL)
			ft_putstr(" ");
		i++;
	}
	if (!(g_minishell.command[g_minishell.num].option[0][0] == '-') && !(g_minishell.command[g_minishell.num].option[0][1] == 'n'))
		ft_putstr("\n");
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

