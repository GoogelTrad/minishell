/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 20:46:59 by elisa             #+#    #+#             */
/*   Updated: 2023/08/22 20:07:07 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_pipe(void)
{
	write(2, "syntax error near unexpected token 'newline'\n", 45);
	g_status = 1;
}

int	verif_slash(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
		{
			write(2, cmd, ft_strlen(cmd));
			write(2, ": ", 2);
			write(1, "No such file or directory\n", 26);
			return (1);
		}
		i++;
	}
	return (0);
}

void	cd_alone(t_minishell *minishell)
{
	char	*var;
	
	var = get_env("HOME", minishell->env);
	if (var)
	{
		chdir(var);
		change_pwd(var, minishell);
	}
	else
	{
		write(2, "cd : HOME not set\n", 18);
		g_status = 1;
	}
	free(var);
}

