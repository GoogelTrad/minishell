/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:41:54 by elisa             #+#    #+#             */
/*   Updated: 2023/09/02 12:52:12 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo(int fd, t_command *c)
{
	int	i;
	int	j;
	int	new_line;

	i = 0;
	new_line = 0;
	if (c->option[0] && c->option[0][0] == '-' && !c->option[0][1])
		i++;
	else if (c->option[0] && c->option[0][0] == '-'
		&& check_option_echo(c->option[0] + 1))
		new_line = 1;
	i = 0 + new_line;
	while (c->option[i])
	{
		j = 0;
		while (c->option[i][j])
			write(fd, &c->option[i][j++], 1);
		if (c->option[i + 1] != NULL)
			write(fd, " ", 1);
		i++;
	}
	if (!new_line)
		write(fd, "\n", 1);
	g_status = 0;
}

/*void	echo(int fd, t_command *c)
{
	int	i;
	int	j;
	int	new_line;

	new_line = 0;
	if (c->option[0] && c->option[0][0] == '-'
		&& check_option_echo(c->option[0] + 1))
		new_line = 1;
	i = 0 + new_line;
	while (c->option[i])
	{
		j = 0;
		while (c->option[i][j])
			write(fd, &c->option[i][j++], 1);
		if (c->option[i + 1] != NULL)
			write(fd, " ", 1);
		i++;
	}
	if (!new_line)
		write(fd, "\n", 1);
	g_status = 0;
}*/
