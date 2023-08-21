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
	char *var;

	if (!verif_arg_cd(c, minishell))
		return ;
	if (c->option[0])
	{
		c->option[0] = verif_cd(c, minishell);
		if (c->option[0])
			verif = chdir(c->option[0]);
		else
			verif = -1;
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
	else
	{
		var = get_env("HOME", minishell->env);
		if (var)
		{
			chdir(var);
			change_pwd(var, minishell);
		}
		free(var);
	}
	minishell->status = 0;
}

void	old_pwd(int i, t_minishell *minishell)
{
	int		j;
	char	*tmp;
	char	*var_name;

	j = 0;
	while (minishell->env[j] && ft_strncmp(minishell->env[j], "OLDPWD", 6) != 0)
		j++;
	tmp = ft_strdup(minishell->env[i] + 4);
	if (!minishell->env[j])
		add_var_env("OLDPWD", minishell->env[i] + 4, minishell);
	var_name = ft_strndup(minishell->env[j], 7);
	minishell->env[j] = ft_strjoin(var_name, tmp);
	free(tmp);
	free(var_name);
}

void	pwd_back(char *path, int i, int j, t_minishell *minishell)
{
	char	*cpy;
	char	*tmp;
	char	*join;

	j--;
	while (minishell->env[i][j] && minishell->env[i][j] != '/')
		j--;
	cpy = ft_strndup(minishell->env[i] + minishell->cd_n, j - minishell->cd_n);
	tmp = ft_strndup(minishell->env[i], minishell->cd_n);
	join = ft_strjoin(tmp, cpy);
	minishell->env[i] = ft_strdup(join);
	free(join);
	free(tmp);
	if (path[2])
		change_pwd(path + 3, minishell);
	free(cpy);
}

void	pwd_front(char *path, int i, t_minishell *minishell)
{
	int		j;
	char	*cpy;
	char	*tmp;

	j = 0;
	while (path[j] && path[j] != '/')
		j++;
	tmp = ft_strjoin(minishell->env[i], "/");
	cpy = ft_strndup(path, j);
	minishell->env[i] = ft_strjoin(tmp, cpy);
	free(tmp);
	if (path[j + 1])
		change_pwd(path + j + 1, minishell);
	free(cpy);
}

void	change_pwd(char *path, t_minishell *minishell)
{
	int		i;
	int		j;
	char	*tmp;
	char	*join;

	i = 0;
	minishell->cd_n = 0;
	while (ft_strncmp(minishell->env[i], "PWD", 3) != 0)
		i++;
	j = ft_strlen(minishell->env[i]);
	while (minishell->env[i][minishell->cd_n] != '/')
		minishell->cd_n++;
	old_pwd(i, minishell);
	if (path[0] == '/')
	{
		if (path[ft_strlen(path) - 1] == '/')
			path = ft_strndup(path, ft_strlen(path) - 1);
		tmp = ft_strndup(minishell->env[i], minishell->cd_n);
		join = ft_strjoin(tmp, path);
		minishell->env[i] = ft_strdup(join);
		free(join);
		free(tmp);
	}
	else
	{
		if (path && ft_strncmp(path, "..", 2) == 0)
			pwd_back(path, i, j, minishell);
		else if (path && ft_strncmp(path, "..", 2) != 0)
			pwd_front(path, i, minishell);
	}
}
