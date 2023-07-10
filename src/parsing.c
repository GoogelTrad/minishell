/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:16:13 by cmichez           #+#    #+#             */
/*   Updated: 2023/07/10 17:36:11 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell g_minishell;

void	separate_cmd(char *ligne)
{
	int			i;
	char		**res_tot;
	char		**res_ligne;

	i = 0;
	res_tot = separate_quote(ligne, '|');
	while (res_tot[i])
		i++;
	g_minishell.command = malloc(sizeof(t_command) * (i + 1));
	i = 0;
	while (res_tot[i])
	{
		g_minishell.command[i].redi = malloc(sizeof(t_redirection));
		res_ligne = ft_split(res_tot[i], ' ');
		res_ligne = display_quote(res_ligne);
		g_minishell.command[i].cmd = res_ligne[0];
		g_minishell.command[i].fd_in = 0;
		g_minishell.command[i].fd_out = 1;
		g_minishell.command[i].redi->there = 0;
		parse_redi(res_ligne + 1, &g_minishell.command[i]);
		i++;
	}
	g_minishell.command[i].cmd = NULL;
}

char *var_env(char *ligne, int j)
{
	int i;
	int incr;
	char quote;
	char *var;
	char *replace;

	i = 0;
	quote = ' ';
	while (ligne[i])
	{
		quote = choose_quote(ligne[i], quote);
		if (ligne[i] == '$' && quote != '\'')
		{
			j = i++;
			while (ligne[i] && ligne[i] != ' ' && ligne[i] != '$' && ligne[i] != quote && isCharAlnum(ligne[i]))
			{
				quote = choose_quote(ligne[i], quote);
				i++;
			}
			printf("i = %d, ligne [i] = %c\n", i, ligne[i]);
			while(1);
			if (ligne[i] == '$')
			{
				replace = dolar_dolar();
				incr = 2;
			}
			else
			{
				var = ft_strndup(ligne + j, i - j);
				replace = getenv(var + 1);
				if (!replace)
				{
					if (!ft_isalnum(var + 1))
						replace = ft_strdup(var + 1);
					else if (ft_isdigit(var[1]))
					{
						replace = ft_strdup(var_arg(g_minishell.av, var, g_minishell.ac));
					}
				}
				incr = 1;
			}
			ligne = replace_value(replace, ligne, j);
			quote = choose_quote(ligne[i], quote);
			i = j + incr;
		}
		i++;
	}
	return (ligne);
}

char	*replace_var(char *var, char **env)
{
	int i;
	int j;
	int lenght_var;
	char *res;

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
	char *temp;
	int verif;
	char *res;
	int j;

	j = i++;
	verif = 0;
	if (!isCharAlnum(ligne[j + 1]) || !ligne[j + 1])
		verif = 1;
	while (ligne[i] && ligne[i] != ' ' && ligne[i] != '$' && ligne[i] != '"' && isCharAlnum(ligne[i]))
		i++;
	if (verif)
		temp = ft_strndup(ligne + j, ft_strlen(ligne) - j);
	else
		temp = ft_strndup(ligne + i, ft_strlen(ligne) - i);
	res = ft_strndup(ligne, j);
	res = ft_strjoin(res, var);
	res = ft_strjoin(res, temp);
	free(temp);
	return (res);
}

char **copy_env(char **env)
{
	int i;
	char **copy;
	
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
