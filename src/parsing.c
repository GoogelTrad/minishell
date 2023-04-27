/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:16:13 by cmichez           #+#    #+#             */
/*   Updated: 2023/04/28 01:07:01 by cmichez          ###   ########.fr       */
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
	//affiche(command);
	return (command);
}

char *var_env(char *ligne, char **env)
{
	int i;
	int j;
	char *var;
	char *replace;

	i = 0;
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
	replace = replace_var(var, env);
	replace_value(replace, ligne);
	return (var);
}

char	*replace_var(char *var, char **env)
{
	int i;
	int j;
	int lenght_env;
	int lenght_var;
	char *res;

	i = 0;
	lenght_var = ft_strlen(var);
	while(env[i] && ft_strncmp(var, env[i], lenght_var) != 0)
		i++;
	j = i;
	i = 0;
	while (env[j] && env[j][i] != '=')
		i++;
	printf("coucou avant le while\n");
	lenght_env = ft_strlen(env[j]) - ++i;
	printf("coucou apres le strlen\n");
	res = ft_strndup(env[j] + i, lenght_env);
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
	j = i;
	while (ligne[i] && ligne[i] != ' ')
		i++;
	temp = ft_strndup(ligne + i, ft_strlen(ligne) - i);
	printf("temp = %s\n", temp);
	res = ft_strndup(ligne, j);
	res = ft_strjoin(res, var);
	res = ft_strjoin(res, temp);
	printf("res = %s\n", res);
	return (res);
}

/*
Il y a un seg fault au  niveau du strlen dans replace_env, regarde si on depasse pas le tableau de env et si on
regarde pas au mauvais endroit
Il faut aussi gerer le cas ou y'a pas de variable d'env dans la commande.
*/