/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:32:33 by elisa             #+#    #+#             */
/*   Updated: 2023/05/01 17:26:56 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ~echo -n ou echo "-n" ne fait rien
void	echo(t_command command)
{
	int	i;
	int	new_line;

	new_line = 0;
	if (!(command.option[0][0] == '-') && !(command.option[0][1] == 'n'))
	{
		ft_putstr(command.option[0]);
		ft_putstr("\n");
	}	
	if (command.option && command.option[0][0] == '-'
		&& check_option_echo(command.option[1] + 1))
		new_line = 1;
	i = 1 + new_line;
	while (command.option[i])
	{
		ft_putstr(command.option[i]);
		if (command.option[i + 1] != NULL)
			ft_putstr(" ");
		i++;
	}
}
