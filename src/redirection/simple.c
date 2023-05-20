/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:02:29 by cmichez           #+#    #+#             */
/*   Updated: 2023/05/20 18:04:26 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_minishell g_minishell;

void simple_droite(void)
{
	int fd;
	char *ligne;
	int i;

	i = 0;
	fd = open(var_env("$PWD", g_minishell.env), O_CREAT);
	while (g_minishell.command->option[i])
	{
		ligne = ft_strjoin(ligne, g_minishell.command->option[i]);
		ligne = ft_strjoin(ligne, " ");
		i++;
	}
	i = 0;
	while (ligne[i])
	{
		write(fd, &ligne[i], 1);
		i++;
	}
}