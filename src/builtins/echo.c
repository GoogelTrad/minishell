/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:41:54 by elisa             #+#    #+#             */
/*   Updated: 2023/07/25 14:29:00 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_minishell	g_minishell;

void	echo(int fd, t_command *c)
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
	if (c->option[0] == NULL || !(c->option[0][0] == '-'
		&& c->option[0][1] == 'n'))
		write(fd, "\n", 1);
	g_minishell.status = 0;
}