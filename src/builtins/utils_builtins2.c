/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:32:06 by cmichez           #+#    #+#             */
/*   Updated: 2023/08/23 11:41:27 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*cd_home_moins(t_minishell *minishell, t_command *c)
{
	char	*name;

	name = get_env("OLDPWD", minishell->env);
	if (!name)
	{
		write(2, "cd : ", 5);
		write(2, c->option[0], ft_strlen(c->option[0]));
		write(2, ": No such file or directory\n", 28);
		g_status = 1;
		return (NULL);
	}
	return (name);
}

char	*cd_moins(t_minishell *minishell)
{
	char	*name;

	name = get_env("OLDPWD", minishell->env);
	if (!name)
	{
		write(2, "cd : OLDPWD not set\n", 20);
		g_status = 1;
		return (NULL);
	}
	printf("%s\n", name);
	return (name);
}

int	verif_arg_cd(t_command *c)
{
	if (c->option[0] && c->option[1])
	{
		write(2, "cd: too many arguments\n", 24);
		g_status = 1;
		return (0);
	}
	return (1);
}

char	*verif_cd(t_command *c, t_minishell *minishell, int *verif)
{
	char	*res;

	res = c->option[0];
	if (c->option[0][0] == '-' && !c->option[0][1])
	{
		free(res);
		res = cd_moins(minishell);
	}
	else if (c->option[0][0] == '~' && c->option[0][1] == '-'
		&& !c->option[0][2])
	{
		free(res);
		res = cd_home_moins(minishell, c);
	}
	if (!res)
		*verif = -2;
	return (res);
}

void	absolute_path(char *path, t_minishell *minishell, int i)
{
	char	*tmp;
	char	*join;

	if (path[ft_strlen(path) - 1] == '/')
		path = ft_strndup(path, ft_strlen(path) - 1);
	tmp = ft_strndup(minishell->env[i], minishell->cd_n);
	join = ft_strjoin(tmp, path);
	if (minishell->env[i])
		free(minishell->env[i]);
	minishell->env[i] = ft_strdup(join);
	free(join);
	free(tmp);
}
