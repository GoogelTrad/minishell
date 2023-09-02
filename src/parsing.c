/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:16:13 by cmichez           #+#    #+#             */
/*   Updated: 2023/09/02 21:31:14 by cmichez          ###   ########.fr       */
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

char	*join_all(char *ligne, char *var, char *temp, int j)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strndup(ligne, j);
	tmp2 = ft_strjoin(tmp, var);
	free(tmp);
	tmp = ft_strjoin(tmp2, temp);
	free(tmp2);
	return (tmp);
}

char	*replace_value(char *var, char *ligne, int i)
{
	char	*temp;
	int		verif;
	char	*res;
	int		j;

	j = i++;
	verif = 0;
	if (!ischaralnum(ligne[j + 1]) || !ligne[j + 1])
		verif = 1;
	while (ligne[i] && ligne[i] != ' ' && ligne[i] != '$'
		&& ligne[i] != '"' && ischaralnum(ligne[i]))
		i++;
	if ((ligne[i] == '$' || ligne[i] == '?') && ligne[i - 1] == '$')
		verif = 2;
	if (verif == 1)
		temp = ft_strndup(ligne + j, ft_strlen(ligne) - j);
	else if (verif == 2)
		temp = ft_strndup(ligne + j + 2, ft_strlen(ligne) - j);
	else
		temp = ft_strndup(ligne + i, ft_strlen(ligne) - i);
	res = join_all(ligne, var, temp, j);
	free(temp);
	return (res);
}
