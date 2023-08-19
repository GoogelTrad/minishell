/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:40:20 by elisa             #+#    #+#             */
/*   Updated: 2023/08/19 20:55:17 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(int fd)
{
	char	*result;
	int		i;

	i = 0;
	result = NULL;
	result = getcwd(result, 0);
	while (result[i])
		write(fd, &result[i++], 1);
	free(result);
	write(fd, "\n", 1);
}
