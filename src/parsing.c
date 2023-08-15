/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:16:13 by cmichez           #+#    #+#             */
/*   Updated: 2023/08/15 13:07:15 by cmichez          ###   ########.fr       */
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

void	separate_cmd(char *ligne, t_minishell **minishell)
{
	int			i;
	char		**res_tot;
	char		**res_ligne;

	i = 0;
	if (verif_line(ligne) == 0)
		printf("coucou\n");
	res_tot = separate_quote(ligne, '|');
	while (res_tot[i])
		i++;
	(*minishell)->command = malloc(sizeof(t_command) * (i + 1));
	i = 0;
	while (res_tot[i])
	{
		(*minishell)->command[i].redi = malloc(sizeof(t_redirection));
		res_ligne = ft_split(res_tot[i], ' ', 0);
		res_ligne = display_quote(res_ligne);
		(*minishell)->command[i].cmd = res_ligne[0];
		(*minishell)->command[i].fd_in = 0;
		(*minishell)->command[i].fd_out = 1;
		(*minishell)->command[i].redi->there = 0;
		parse_redi(res_ligne + 1, &(*minishell)->command[i]);
		i++;
	}
	(*minishell)->command[i].cmd = NULL;
}

char	*var_env(char *ligne, int j, t_minishell *minishell)
{
	int		i;
	char	quote;
	char	*replace;

	i = 0;
	quote = ' ';
	while (ligne[i])
	{
		quote = choose_quote(ligne[i], quote, &i, 0);
		if (ligne[i] == '$' && quote != '\'')
		{
			j = i++;
			while (ligne[i] && ligne[i] != ' ' && ligne[i] != '$'
				&& ligne[i] != quote && ischaralnum(ligne[i]))
				quote = choose_quote(ligne[i], quote, &i, 1);
			replace = type_of_var(ligne, i, j, minishell);
			ligne = replace_value(replace, ligne, j);
			quote = choose_quote(ligne[i], quote, &i, 0);
			if (ligne[j + minishell->incr])
				i = j + minishell->incr;
		}
		i++;
	}
	return (ligne);
}

char	*replace_var(char *var, char **env)
{
	int		i;
	int		j;
	int		lenght_var;
	char	*res;

	i = 0;
	lenght_var = ft_strlen(var);
	while (env[i] && ft_strncmp(var, env[i], lenght_var) != 0)
		i++;
	if (!env[i])
		return (var);
	j = i;
	i = 0;
	while (env[j][i] && env[j][i] != '=')
		i++;
	i++;
	res = ft_strdup(env[j] + i);
	return (res);
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
	res = ft_strndup(ligne, j);
	res = ft_strjoin(res, var);
	res = ft_strjoin(res, temp);
	free(temp);
	return (res);
}
