/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:16:40 by cmichez           #+#    #+#             */
/*   Updated: 2023/07/10 17:09:57 by cmichez          ###   ########.fr       */
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
