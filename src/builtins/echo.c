/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:41:54 by elisa             #+#    #+#             */
/*   Updated: 2023/09/03 11:56:27 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_option(char **str)
{
	int	i;
	int	lenskip;
	int	check;

	i = 0;
	lenskip = 0;
	while (str[i])
	{
		check = 0;
		if (str[i][0] == '-')
		{
			if (check_option_echo(str[i] + 1))
				lenskip += 1;
			else
				return (lenskip);
			check = 1;
		}
		if (check && str[i + 1] != NULL && !check_option_echo(str[i + 1] + 1))
			return (lenskip);
		i++;
	}
	return (lenskip);
}

void	echo(int fd, t_command *c)
{
	int	i;
	int	j;
	int	new_line;
	int	skip;

	i = 0;
	new_line = 0;
	skip = check_option(c->option);
	if (c->option[0] && c->option[0][0] == '-' && !c->option[0][1])
		i++;
	else if (c->option[0] && c->option[0][0] == '-' && skip)
		new_line = 1;
	i = 0 + skip;
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
