/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:36:48 by elisa             #+#    #+#             */
/*   Updated: 2023/08/19 16:30:19 by elisa            ###   ########.fr       */
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
				write(minishell->fd, "\n", 1);
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
		minishell->status = 127;
		write(2, "cd: ", 4);
		write(2, c->option[0], ft_strlen(c->option[0]));
		write(2, ": ", 3);
		write(2, "No such file or directory\n", 26);
		return ;
	}
	else
		aff_env(fd, minishell);
	minishell->status = 0;
}

void	init_env(char **env, t_minishell *minishell)
{
	char	*buf;

	buf = NULL;
	if (env[0])
	{
		minishell->env = copy_env(env);
		return ;
	}
	minishell->env = malloc(sizeof(char *) * 4);
	minishell->env[0] = ft_strjoin("PWD=", getcwd(buf, 0));
	minishell->env[1] = ft_strdup("SHLVL=1");
	minishell->env[2] = ft_strjoin("_=", getcwd(buf, 0));
	minishell->env[2] = ft_strjoin(minishell->env[2], "/");
	minishell->env[2] = ft_strjoin(minishell->env[2], minishell->av[0]);
	free(buf);
}
