/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:02:29 by cmichez           #+#    #+#             */
/*   Updated: 2023/08/15 13:10:35 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	simple_droite(t_command *c)
{
	c->fd_out = open(c->redi->word, O_CREAT | O_RDWR | O_TRUNC, 0644);
}

void	simple_gauche(t_command *c, t_minishell *minishell)
{
	int		pipes[2];
	int		fd;
	char	buf;

	pipe(pipes);
	if (open(c->redi->word, O_RDONLY) != -1)
		fd = open(c->redi->word, O_RDONLY);
	else
	{
		write(2, c->redi->word, ft_strlen(c->redi->word));
		write(2, ": ", 3);
		minishell->status = put_error(errno);
		return ;
	}
	c->fd_in = pipes[0];
	while (read(fd, &buf, 1))
		write(pipes[1], &buf, 1);
	close(fd);
	close(pipes[1]);
}
