/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:16:13 by cmichez           #+#    #+#             */
/*   Updated: 2023/04/27 22:20:34 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*separate_cmd(char *cmd)
{
	int			i;
	char		**res_tot = NULL;
	char		**res_ligne;
	t_command	*command;

	i = 0;
	if (ft_strcmp(cmd, "exit") == 0)
		exit(0);
	res_tot = separate_quote(cmd, '|');
	while (res_tot[i])
		i++;
	command = malloc(sizeof(t_command) * (i + 1));
	i = 0;
	while (res_tot[i])
	{
		res_ligne = ft_split(res_tot[i], ' ');
		command[i].cmd = res_ligne[0];
		command[i].option = res_ligne + 1;
		i++;
	}
	command[i].cmd = NULL;
	affiche(command);
	return (command);
}

char *var_env(char *ligne, char **env)
{
	int i;
	int j;
	char *var;

	i = 0;
	(void)env;
	while (ligne[i])
	{
		if (ligne[i] == '$')
		{
			j = i;
			while (ligne[i] && ligne[i] != ' ')
				i++;
			var = ft_strndup(ligne + j + 1, i - j);
		}
		i++;
	}
	replace_var(var, env);
	return (var);
}

char	*replace_var(char *var, char **env)
{
	
}