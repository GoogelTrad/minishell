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

#include "minishell.h"

extern t_minishell g_minishell;

void	cd(t_command *c)
{
	int verif;
	
	if (c->option[0])
	{
		verif = chdir(c->option[0]);
		if (verif == -1)
			printf("cd %s : No such file or directory\n", c->option[0]);
		else
			change_pwd(c->option[0]);
	}
}

void    old_pwd(int i)
{
    int j;

    j = 0;
    while (ft_strncmp(g_minishell.env[j], "OLDPWD", 6) != 0)
        j++;
    g_minishell.env[j] = ft_strjoin(ft_strndup(g_minishell.env[j], 7), 
        ft_strdup(g_minishell.env[i] + 4));
}

void    pwd_back(char *path, int i, int j, int n)
{
    char *cpy;

    j--;
    while (g_minishell.env[i][j] != '/')
        j--;
    cpy = ft_strndup(g_minishell.env[i] + n, j - n);
    g_minishell.env[i] = ft_strdup(ft_strjoin(ft_strndup(g_minishell.env[i], n), cpy));
    if (path[2])
        change_pwd(path + 3);
}

void    pwd_front(char *path, int i)
{
    int j;
    char *cpy;

    j = 0;
    while(path[j] != '/')
        j++;
    g_minishell.env[i] = ft_strjoin(g_minishell.env[i], "/");
    cpy = ft_strndup(path, j);
    g_minishell.env[i] = ft_strjoin(g_minishell.env[i], cpy);
    if (path[j + 1])
        change_pwd(path + j + 1);
}

void	change_pwd(char *path)
{
	int i;
	int j;
	int n;

	i = 0;
	n = 0;
	while (ft_strncmp(g_minishell.env[i], "PWD", 3) != 0)
		i++;
	j = ft_strlen(g_minishell.env[i]);
	while (g_minishell.env[i][n] != '/')
		n++;
    old_pwd(i);
	if (path[0] == '/')
	{	
		if (path[ft_strlen(path) - 1] == '/')
			path = ft_strndup(path, ft_strlen(path) - 1);
		g_minishell.env[i] = ft_strdup(ft_strjoin(ft_strndup(g_minishell.env[i], n), path));
	}
	else
	{
		if (path && ft_strncmp(path, "..", 2) == 0)
			pwd_back(path, i, j, n);
		else if (path && ft_strncmp(path, "..", 2) != 0)
			pwd_front(path, i);
	}
}