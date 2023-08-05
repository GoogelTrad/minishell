/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:16:40 by cmichez           #+#    #+#             */
/*   Updated: 2023/08/03 16:42:00 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char choose_quote(char c, char quote)
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
	return (quote);
}

int put_error(int type)
{
	write(2, strerror(type), ft_strlen(strerror(type)));
	write(2, "\n", 1);
	return (type);
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