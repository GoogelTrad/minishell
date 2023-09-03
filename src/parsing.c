/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:16:13 by cmichez           #+#    #+#             */
/*   Updated: 2023/09/03 16:16:31 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(char **env)
{
	int		i;
	char	**copy;

	i = 0;
	while (env[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		copy[i] = ft_strdup(env[i]);
		i++;
	}
	copy[i] = 0;
	return (copy);
}

int	separate_cmd(char *ligne, t_minishell *minishell)
{
	int			i;
	char		**res_tot;
	char		**res_ligne;

	i = 0;
	if (verif_line(ligne) == 0)
		return (0);
	res_tot = separate_quote(ligne, '|');
	while (res_tot[i])
		i++;
	minishell->command = malloc(sizeof(t_command) * (i + 1));
	i = 0;
	while (res_tot[i])
	{
		minishell->command[i].redi = redi(res_tot[i]);
		res_ligne = ft_split(res_tot[i], ' ', 0);
		res_ligne = parse_quote(res_ligne, minishell);
		parse_redi(res_ligne, &minishell->command[i]);
		free_double_tab(res_ligne);
		i++;
	}
	free_double_tab(res_tot);
	minishell->command[i].cmd = NULL;
	return (1);
}

char	*var_env(char *var, t_minishell *minishell)
{
	int		i;

	i = 0;
	if (var[0] == '$')
		return (dolar_dolar());
	else if (var[0] == '?')
		return (ft_itoa(g_status));
	else
	{
		if (var_size(var) == 0)
			return ("$");
		while (minishell->env[i])
		{
			if (ft_strncmp(minishell->env[i], var,
					env_var_size(minishell->env[i])) == 0)
				return (ft_strdup(minishell->env[i] + var_size(var) + 1));
			i++;
		}
	}
	return (NULL);
}

