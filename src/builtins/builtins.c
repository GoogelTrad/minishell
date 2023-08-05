/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:32:33 by elisa             #+#    #+#             */
/*   Updated: 2023/08/03 16:24:06 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset(t_command *c, t_minishell *minishell)
{
	int	i;

	i = 0;
	if (var_env(c->option[0], 0, minishell))
	{
		while (minishell->env[i] && ft_strncmp(c->option[0],
				minishell->env[i], ft_strlen(c->option[0])) != 0)
			i++;
		if (minishell->env[i])
			free(minishell->env[i]);
		while (minishell->env[i])
		{
			minishell->env[i] = minishell->env[i + 1];
			i++;
		}
	}
	minishell->status = 0;
}
