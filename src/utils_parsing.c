/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:16:40 by cmichez           #+#    #+#             */
/*   Updated: 2023/07/25 14:52:00 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell g_minishell;

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