/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 20:46:59 by elisa             #+#    #+#             */
/*   Updated: 2023/09/02 17:09:39 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_pipe(char *msg)
{
	write(2, "syntax error near unexpected token '", 37);
	write(2, msg, ft_strlen(msg));
	write(2, "'\n", 2);
	g_status = 1;
}

int	verif_slash(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
		{
			g_status = 127;
			write(2, cmd, ft_strlen(cmd));
			write(2, ": ", 2);
			write(2, "No such file or directory\n", 26);
			return (1);
		}
		i++;
	}
	return (0);
}

void	cd_alone(t_minishell *minishell)
{
	char	*var;

	var = get_env("HOME", minishell->env);
	if (var)
	{
		chdir(var);
		change_pwd(var, minishell);
	}
	else
	{
		write(2, "cd : HOME not set\n", 18);
		g_status = 1;
	}
	free(var);
}

int	redi_norme(t_command *c, t_minishell *minishell)
{
	if (ft_strcmp(c->redi->type, ">") == 0)
	{
		if (!simple_droite(c))
			return (0);
	}
	else if (ft_strcmp(c->redi->type, ">>") == 0)
	{
		if (!double_droite(c))
			return (0);
	}
	else if (ft_strcmp(c->redi->type, "<") == 0)
	{
		if (!simple_gauche(c))
			return (0);
	}
	else if (ft_strcmp(c->redi->type, "<<") == 0)
	{
		if (!double_gauche(c, minishell))
			return (0);
	}
	return (1);
}

int	exec_relative_path(char *path, int *verif, t_minishell *minishell,
	t_command *c)
{
	char	*tmp;
	char	*fusion;

	tmp = ft_strjoin(path, "/");
	fusion = ft_strjoin(tmp, c->cmd);
	free(tmp);
	if (open(fusion, O_RDONLY) > -1 && c->cmd)
	{
		minishell->pid = exec_fork(fusion, c, minishell, 1);
		(*verif) = 1;
		return (0);
	}
	free(fusion);
	return (1);
}
