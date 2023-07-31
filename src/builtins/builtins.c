/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:32:33 by elisa             #+#    #+#             */
/*   Updated: 2023/07/21 17:55:46 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_minishell	g_minishell;

void	unset(t_command *c)
{
	int	i;

	i = 0;
	if (var_env(c->option[0], 0))
	{
		while (g_minishell.env[i] && ft_strncmp(c->option[0],
				g_minishell.env[i], ft_strlen(c->option[0])) != 0)
			i++;
		if (g_minishell.env[i])
			free(g_minishell.env[i]);
		while (g_minishell.env[i])
		{
			g_minishell.env[i] = g_minishell.env[i + 1];
			i++;
		}
	}
	g_minishell.status = 0;
}
