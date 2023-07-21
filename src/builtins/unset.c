/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 18:11:33 by elisa             #+#    #+#             */
/*   Updated: 2023/07/20 14:59:19 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_minishell g_minishell;

size_t	env_size(char *env)
{
	size_t		i = 0;

	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

void		ft_free(t_minishell *env)
{
	if (env->env == NULL)
	{
		free(env->env);
		return ;
	}
}

void ft_unset(t_command *c)
{
	int i = 0;
	size_t size;

	if (getenv(c->option[1]))
	{
		size = env_size(c->option[1]);
		while (ft_strncmp(c->option[1], g_minishell.env[i], size) != 0)
			i++;
		
	}
}