/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:51:59 by cmichez           #+#    #+#             */
/*   Updated: 2023/05/05 15:51:59 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

void	belle_exec(t_command *c)
{
	int	pipes[2];

	pipe(pipes);
	exec_redi(c);
	if ((c + 1)->cmd)
	{
		if (c->fd_out == 1)
			c->fd_out = pipes[1];
		(c + 1)->fd_in = pipes[0];
	}
	exec(c->fd_out, c);
	if ((c + 1)->cmd)
		belle_exec(c + 1);
}

void	exec(int fd, t_command *c)
{
	if (ft_strcmp(c->cmd, "echo") == 0)
		echo(fd, c);
	else if (ft_strcmp(c->cmd, "exit") == 0)
		ft_exit(c);
	else if (ft_strcmp(c->cmd, "pwd") == 0)
		pwd(fd);
	else if (ft_strcmp(c->cmd, "env") == 0)
		env(fd, c);
	else if (ft_strcmp(c->cmd, "cd") == 0)
		cd(c);
	else if (ft_strcmp(c->cmd, "unset") == 0)
		unset(c);
	else if (ft_strcmp(c->cmd, "export") == 0)
		export(c);
	else
		exec_others(c);
}

void	exec_redi(t_command *c)
{
	while (c->redi->there)
	{
		if (ft_strcmp(c->redi->type, ">") == 0)
			simple_droite(c);
		else if (ft_strcmp(c->redi->type, ">>") == 0)
			double_droite(c);
		else if (ft_strcmp(c->redi->type, "<") == 0)
			simple_gauche(c);
		else if (ft_strcmp(c->redi->type, "<<") == 0)
			double_gauche(c);
		c->redi = c->redi->next_redi;
	}
}

void	exec_others(t_command *c)
{
	char	**path;
	char	*fusion;
	int		i;

	i = 0;
	if (open(c->cmd, O_RDONLY) > -1)
		exec_fork(c->cmd, c);
	else
	{
		path = ft_split(var_env("$PATH", g_minishell.env), ':');
		while (path[i])
		{
			fusion = ft_strjoin(path[i], "/");
			fusion = ft_strjoin(fusion, c->cmd);
			if (open(fusion, O_RDONLY) > -1)
			{
				exec_fork(fusion, c);
				break ;
			}
			i++;
		}
	}
}

void	exec_fork(char *fichier, t_command *c)
{
	int	pid;
	int	status;

	fusion_exec(c);
	pid = fork();
	if (pid == 0)
	{
		if (c->cmd)
			dup2(c->fd_out, 1);
		if (c->fd_in != 0)
			dup2(c->fd_in, 0);
		execve(fichier, g_minishell.fusion, g_minishell.env);
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
	if (c->fd_out != 1)
		close(c->fd_out);
}

void	fusion_exec(t_command *c)
{
	int	i;

	i = 0;
	while (c->option[i])
		i++;
	g_minishell.fusion = malloc(sizeof(char *) + (i + 1));
	i = 0;
	g_minishell.fusion[0] = ft_strdup(c->cmd);
	while (c->option[i])
	{
		g_minishell.fusion[i + 1] = ft_strdup(c->option[i]);
		i++;
	}
	g_minishell.fusion[i + 1] = NULL;
}
