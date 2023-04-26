/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:16:13 by cmichez           #+#    #+#             */
/*   Updated: 2023/04/26 19:08:05 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	**separate_cmd(t_command **command, char *cmd)
{
	int i;
	char **res_tot = NULL;
	char **res_ligne;

	i = 0;
	if (ft_strcmp(cmd, "exit") == 0)
		exit(0);
	res_tot = double_quote(cmd, '|');
	while (res_tot[i + 1])
	{
		command[i] = malloc(sizeof(char *) + 1);
		i++;
	}
	i = 0;
	while (res_tot[i])
	{
		res_ligne = ft_split(res_tot[i], ' ');
		command[i]->cmd = res_ligne[0];
		command[i]->option = res_ligne + 1;
		i++;
	}
	affiche(command);
	return (command);
}
