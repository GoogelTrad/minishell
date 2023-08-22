/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 18:11:33 by elisa             #+#    #+#             */
/*   Updated: 2023/08/22 11:44:17 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	env_size(char *env)
{
	size_t		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

void	ft_free(t_minishell *env)
{
	if (env->env == NULL)
	{
		free(env->env);
		return ;
	}
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	unset(t_command *c, t_minishell *minishell)
{
	int	i;

	i = 0;
	if (c->option[0] && var_env(c->option[0], 0, minishell))
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
		minishell->size_env -= 1;
	}
	g_status = 0;
}
