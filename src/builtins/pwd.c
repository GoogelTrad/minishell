/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:40:20 by elisa             #+#    #+#             */
/*   Updated: 2023/07/20 14:53:44 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_minishell	g_minishell;

void	pwd(int fd)
{
	char	*result;
	int		i;

	i = 0;
	result = var_env("$PWD", 0);
	if (result != NULL)
	{
		while (result[i])
			write(fd, &result[i++], 1);
	}
	write(fd, "\n", 1);
}
