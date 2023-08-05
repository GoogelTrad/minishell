/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 22:10:48 by cmichez           #+#    #+#             */
/*   Updated: 2023/06/19 22:10:48 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd(t_command *c, t_minishell *minishell)
{
	int	verif;

	if (c->option[0])
	{
		verif = chdir(c->option[0]);
		if (verif == -1)
		{
			write(2, "cd: ", 4);
			write(2, c->option[0], ft_strlen(c->option[0]));
			write(2, ": ", 3);
			minishell->status = put_error(errno);
			return ;
		}
		else
			change_pwd(c->option[0], minishell);
	}
	minishell->status = 0;
}

void	old_pwd(int i, t_minishell *minishell)
{
	int	j;

	j = 0;
	while (ft_strncmp(minishell->env[j], "OLDPWD", 6) != 0)
		j++;
	minishell->env[j] = ft_strjoin(ft_strndup(minishell->env[j], 7), 
			ft_strdup(minishell->env[i] + 4));
}

void	pwd_back(char *path, int i, int j, int n, t_minishell *minishell)
{
	char	*cpy;

	j--;
	while (minishell->env[i][j] && minishell->env[i][j] != '/')
		j--;
	cpy = ft_strndup(minishell->env[i] + n, j - n);
	minishell->env[i] = ft_strdup(ft_strjoin
			(ft_strndup(minishell->env[i], n), cpy));
	if (path[2])
		change_pwd(path + 3, minishell);
}

void	pwd_front(char *path, int i, t_minishell *minishell)
{
	int		j;
	char	*cpy;

	j = 0;
	while (path[j] && path[j] != '/')
		j++;
	minishell->env[i] = ft_strjoin(minishell->env[i], "/");
	cpy = ft_strndup(path, j);
	minishell->env[i] = ft_strjoin(minishell->env[i], cpy);
	if (path[j + 1])
		change_pwd(path + j + 1, minishell);
}

void	change_pwd(char *path, t_minishell *minishell)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	n = 0;
	while (ft_strncmp(minishell->env[i], "PWD", 3) != 0)
		i++;
	j = ft_strlen(minishell->env[i]);
	while (minishell->env[i][n] != '/')
		n++;
	old_pwd(i, minishell);
	if (path[0] == '/')
	{
		if (path[ft_strlen(path) - 1] == '/')
			path = ft_strndup(path, ft_strlen(path) - 1);
		minishell->env[i] = ft_strdup(ft_strjoin
				(ft_strndup(minishell->env[i], n), path));
	}
	else
	{
		if (path && ft_strncmp(path, "..", 2) == 0)
			pwd_back(path, i, j, n, minishell);
		else if (path && ft_strncmp(path, "..", 2) != 0)
			pwd_front(path, i, minishell);
	}
}
