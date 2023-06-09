/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epraduro <epraduro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:02:29 by cmichez           #+#    #+#             */
/*   Updated: 2023/07/06 13:08:05 by epraduro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_minishell	g_minishell;

void	simple_droite(t_command *c)
{
	c->fd_out = open(c->redi->word, O_CREAT | O_RDWR | O_TRUNC, 0644);
}

void	simple_gauche(t_command *c)
{
	int		pipes[2];
	int		fd;
	char	buf;

	pipe(pipes);
	fd = open(c->redi->word, O_RDONLY);
	c->fd_in = pipes[0];
	while (read(fd, &buf, 1))
		write(pipes[1], &buf, 1);
	close(fd);
	close(pipes[1]);
}
