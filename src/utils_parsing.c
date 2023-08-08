/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:16:40 by cmichez           #+#    #+#             */
/*   Updated: 2023/08/06 17:38:51 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	choose_quote(char c, char quote, int *i, int verif)
{
	if (c == '\'')
		quote = '\'';
	else if (c == '"' && quote != '\'')
		quote = '"';
	else if (c == '"' && quote == '"')
		quote = ' ';
	else if (c == '\'' && quote == '\'')
		quote = ' ';
	else if (c == '\'' && quote != '\'')
		quote = ' ';
	if (verif == 1)
		(*i)++;
	return (quote);
}

int	put_error(int type)
{
	write(2, strerror(type), ft_strlen(strerror(type)));
	write(2, "\n", 1);
	return (type);
}

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

char	*replace_var_env(char *ligne, int i, int j, t_minishell *minishell)
{
	char	*replace;
	char	*var;

	var = ft_strndup(ligne + j, i - j);
	replace = get_env(var + 1, minishell->env);
	if (!replace)
	{
		if (!ft_isalnum(var + 1))
			replace = ft_strdup(var + 1);
		else if (ft_isdigit(var[1]))
		{
			replace = ft_strdup(var_arg(minishell->av, var, minishell->ac));
		}
	}
	minishell->incr = 2;
	return (replace);
}

char	*type_of_var(char *ligne, int i, int j, t_minishell *minishell)
{
	char	*replace;

	if (ligne[i] == '?')
	{
		replace = ft_itoa(minishell->status);
		minishell->incr = 2;
	}
	else if (ligne[i] == '$')
		replace = dolar_dolar(minishell);
	else
		replace = replace_var_env(ligne, i, j, minishell);
	return (replace);
}
