/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:40:20 by elisa             #+#    #+#             */
/*   Updated: 2023/08/03 16:33:58 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(int fd, t_minishell *minishell)
{
	char	*result;
	int		i;

	i = 0;
	result = var_env("$PWD", 0, minishell);
	if (result != NULL)
	{
		while (result[i])
			write(fd, &result[i++], 1);
		free(result);
	}
	write(fd, "\n", 1);
}
