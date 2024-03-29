/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:40:20 by elisa             #+#    #+#             */
/*   Updated: 2023/08/31 13:47:32 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(int fd, t_minishell *minishell)
{
	char	*result;
	int		i;

	i = 0;
	result = NULL;
	result = get_env("PWD", minishell->env);
	while (result[i])
		write(fd, &result[i++], 1);
	free(result);
	write(fd, "\n", 1);
	g_status = 0;
}
