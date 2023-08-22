/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:02:29 by cmichez           #+#    #+#             */
/*   Updated: 2023/08/22 11:45:36 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	simple_droite(t_command *c)
{
	if (!verif_redi(c->redi->word))
		return (0);
	c->fd_out = open(c->redi->word, O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (1);
}

int	simple_gauche(t_command *c)
{
	int		pipes[2];
	int		fd;
	char	buf;

	if (!verif_redi(c->redi->word))
		return (0);
	pipe(pipes);
	if (open(c->redi->word, O_RDONLY) != -1)
		fd = open(c->redi->word, O_RDONLY);
	else
	{
		write(2, c->redi->word, ft_strlen(c->redi->word));
		write(2, ": ", 3);
		g_status = put_error(errno);
		return (0);
	}
	c->fd_in = pipes[0];
	while (read(fd, &buf, 1))
		write(pipes[1], &buf, 1);
	close(fd);
	close(pipes[1]);
	return (1);
}

int	redi_cmd(t_command *c)
{
	if (ft_strcmp(c->cmd, "<") == 0 || ft_strcmp(c->cmd, "<<") == 0
		|| ft_strcmp(c->cmd, ">") == 0 || ft_strcmp(c->cmd, ">>") == 0)
		return (1);
	else
		return (0);
}
