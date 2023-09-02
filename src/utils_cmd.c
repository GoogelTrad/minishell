/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:45:54 by cmichez           #+#    #+#             */
/*   Updated: 2023/09/01 13:45:54 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verif_cmd(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (!ischaralnum(cmd[i]))
		{
			g_status = 2;
			write(2, "syntax error near unexpected token '", 37);
			write(2, &cmd[i], 1);
			write(2, "'\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}
