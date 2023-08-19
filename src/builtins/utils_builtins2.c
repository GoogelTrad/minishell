/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:32:06 by cmichez           #+#    #+#             */
/*   Updated: 2023/08/19 23:20:46 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*cd_home_moins(t_minishell *minishell)
{
	return (get_env("OLDPWD", minishell->env));
}

char	*cd_moins(t_minishell *minishell)
{
	char	*name;

	name = get_env("OLDPWD", minishell->env);
	printf("%s\n", name);
	return (name);
}

int	verif_arg_cd(t_command *c, t_minishell *minishell)
{
	if (c->option[0] && c->option[1])
	{
		write(2, "cd: too many arguments\n", 24);
		minishell->status = 1;
		return (0);
	}
	return (1);
}

char	*verif_cd(t_command *c, t_minishell *minishell)
{
	char	*res;

	res = c->option[0];
	if (c->option[0][0] == '-' && !c->option[0][1])
		res = cd_moins(minishell);
	else if (c->option[0][0] == '~' && c->option[0][1] == '-'
		&& !c->option[0][2])
		res = cd_home_moins(minishell);
	return (res);
}
