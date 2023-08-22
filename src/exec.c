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

void	belle_exec(t_command *c, t_minishell *minishell)
{
	int	pipes[2];
	int	pid;

	pipe(pipes);
	if (!exec_redi(c, minishell))
		return ;
	if ((c + 1)->cmd)
	{
		if (c->fd_out == 1)
			c->fd_out = pipes[1];
		(c + 1)->fd_in = pipes[0];
	}
	signal(SIGINT, &get_sigint_cmd);
	exec(c->fd_out, c, minishell);
	pid = minishell->pid;
	if ((c + 1)->cmd)
		belle_exec(c + 1, minishell);
	close(pipes[0]);
	waitpid(pid, &g_status, 0);
}

void	exec(int fd, t_command *c, t_minishell *minishell)
{
	if (ft_strcmp(c->cmd, "echo") == 0)
		echo(fd, c);
	else if (ft_strcmp(c->cmd, "exit") == 0)
		ft_exit(c, minishell);
	else if (ft_strcmp(c->cmd, "pwd") == 0)
		pwd(fd);
	else if (ft_strcmp(c->cmd, "env") == 0)
		env(fd, c, minishell);
	else if (ft_strcmp(c->cmd, "cd") == 0)
		cd(c, minishell);
	else if (ft_strcmp(c->cmd, "unset") == 0)
		unset(c, minishell);
	else if (ft_strcmp(c->cmd, "export") == 0)
		export(c, minishell);
	else
		exec_others(c, 0, minishell);
}

int	exec_redi(t_command *c, t_minishell *minishell)
{
	t_redirection	*tmp;
	
	tmp = c->redi;
	while (c->redi->there)
	{
		if (!redi_norme(c, minishell))
			return (0);
		c->redi = c->redi->next_redi;
	}
	c->redi = tmp;
	return (1);
}

void	exec_others(t_command *c, int verif, t_minishell *minishell)
{
	char	**path;
	char	*var;
	int		i;

	i = 0;
	if (open(c->cmd, O_RDONLY) > -1 && (c->cmd[0] == '/' || c->cmd[0] == '.'))
		exec_fork(c->cmd, c, minishell, 0);
	else
	{
		var = var_env("$PATH", 0, minishell);
		path = ft_split(var, ':', 0);
		free(var);
		while (path[i] && c->cmd[0] != '/' && c->cmd[0] != '.')
		{
			if (!exec_relative_path(path[i], &verif, minishell, c))
				break ;
			i++;
		}
		no_command(verif, c, minishell);
		free_double_tab(path);
	}
}

void	exec_fork(char *fichier, t_command *c, t_minishell *minishell, int i)
{
	fusion_exec(c, minishell);
	minishell->pid = fork();
	if (minishell->pid == 0)
	{
		dup2(c->fd_out, 1);
		if (c->fd_in != 0)
			dup2(c->fd_in, 0);
		if ((c + 1)->cmd)
			close((c + 1)->fd_in);
		if (execve(fichier, minishell->fusion, minishell->env) == -1)
			g_status = put_error(errno);
		else
			g_status = 0;
		exit(1);
	}
	if (c->fd_out != 1)
		close(c->fd_out);
	free_double_tab(minishell->fusion);
	if (i)
		free(fichier);
}
