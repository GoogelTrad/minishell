/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:16:13 by cmichez           #+#    #+#             */
/*   Updated: 2023/05/31 16:09:36 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell g_minishell;

void	separate_cmd(char *cmd)
{
	int			i;
	char		**res_tot = NULL;
	char		**res_ligne;

	i = 0;
	res_tot = separate_quote(cmd, '|');
	while (res_tot[i])
		i++;
	g_minishell.command = malloc(sizeof(t_command) * (i + 1));
	g_minishell.command->redi = malloc(sizeof(t_redirection));
	i = 0;
	while (res_tot[i])
	{
		res_ligne = ft_split(res_tot[i], ' ');
		g_minishell.command[i].cmd = res_ligne[0];
		g_minishell.command[i].redi->there = 0;
		parse_redi(res_ligne + 1, i);
		i++;
	}
	g_minishell.command[i].cmd = NULL;
}

char *var_env(char *ligne, char **env)
{
	int i;
	int j;
	char quote;
	char *var;
	char *replace;

	i = 0;
	quote = ' ';
	while (ligne[i])
	{
		if (ligne[i] == '\'')
			quote = '\'';
		if (ligne[i] == '"' && quote != '\'')
					quote = '"';
		if (ligne[i] == '$' && quote != '\'')
		{
			j = i++;
			while (ligne[i] && ligne[i] != ' ' && ligne[i] != '$' && ligne[i] != quote)
			{
				if (ligne[i] == '"' && quote == '"')
					quote = ' ';
				if (ligne[i] == '\'' && quote == '\'')
					quote = ' ';
				i++;
			}
			var = ft_strndup(ligne + j + 1, i - j - 1);
			replace = replace_var(var, env);
			ligne = replace_value(replace, ligne);
			i = -1;
		}
		if (ligne[i] == '\'' && quote != '\'')
			quote = ' ';
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

char	*replace_value(char *var, char *ligne)
{
	char *temp;
	char *res;
	int i;
	int j;

	i = 0;
	while (ligne[i] && ligne[i] != '$')
		i++;
	j = i++;
	while (ligne[i] && ligne[i] != ' ' && ligne[i] != '$' && ligne[i] != '"')
		i++;
	temp = ft_strndup(ligne + i, ft_strlen(ligne) - i);
	res = ft_strndup(ligne, j);
	res = ft_strjoin(res, var);
	res = ft_strjoin(res, temp);
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
