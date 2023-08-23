/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:36:48 by elisa             #+#    #+#             */
/*   Updated: 2023/08/23 11:47:20 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	aff_env(int fd, t_minishell *minishell)
{
	int	i;
	int	j;

	i = 0;
	while (minishell->env[i])
	{
		j = 0;
		while (minishell->env[i][j])
		{
			if (minishell->env[i][j] == '=')
			{	
				write(fd, minishell->env[i], ft_strlen(minishell->env[i]));
				write(fd, "\n", 1);
				break ;
			}
			j++;
		}
		i++;
	}
}

void	env(int fd, t_command *c, t_minishell *minishell)
{
	if (c->option[0])
	{
		g_status = 127;
		write(2, "cd: ", 4);
		write(2, c->option[0], ft_strlen(c->option[0]));
		write(2, ": ", 3);
		write(2, "No such file or directory\n", 26);
		return ;
	}
	else
		aff_env(fd, minishell);
	g_status = 0;
}

void	init_env(char **env, t_minishell *minishell)
{
	char	*buf;
	char	*tmp;
	char	*cwd;

	buf = NULL;
	if (env[0])
	{
		minishell->env = copy_env(env);
		return ;
	}
	minishell->env = malloc(sizeof(char *) * 4);
	cwd = getcwd(buf, 0);
	minishell->env[0] = ft_strjoin("PWD=", cwd);
	minishell->env[1] = ft_strdup("SHLVL=1");
	minishell->env[2] = ft_strjoin("_=", cwd);
	tmp = ft_strjoin(minishell->env[2], "/");
	free(minishell->env[2]);
	minishell->env[2] = ft_strjoin(tmp, minishell->av[0]);
	free(tmp);
	free(buf);
	free(cwd);
}
