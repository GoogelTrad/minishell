/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 18:11:33 by elisa             #+#    #+#             */
/*   Updated: 2023/09/03 16:25:09 by cmichez          ###   ########.fr       */
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
	int	j;

	j = 0;
	while (c->option[j] && get_env(c->option[0], minishell->env))
	{
		i = 0;
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
		j++;
	}
	g_status = 0;
}
