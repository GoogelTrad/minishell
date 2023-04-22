/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:16:13 by cmichez           #+#    #+#             */
/*   Updated: 2023/04/21 17:36:26 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	separate_cmd(t_command *command, char *cmd)
{
	int i;

	i = 0;
	char **res_tot;
	char **res_ligne;
	if (ft_strcmp(cmd, "exit") == 0)
		exit(0);
	res_tot = ft_split_dq(cmd, '|');
	while (res_tot[i])
	{
		res_ligne = ft_split_dq(res_tot[i], ' ');
		command->cmd = res_ligne[0];
		command->option = res_ligne + 1;
		i++;
		affiche(command);
	}
	
}
