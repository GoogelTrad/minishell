/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:33:33 by elisa             #+#    #+#             */
/*   Updated: 2023/09/03 15:49:36 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	var_size(char *ligne)
{
	int	i;

	i = 0;
	if (*ligne == '?')
		return (1);
	while (ligne[i] && (ischaralnum(ligne[i]) || ligne[i] == '_'))
		i++;
	return (i);
}

char	*replace_char(char *ligne, int i)
{
	while (ligne[i])
	{
		ligne[i] = ligne[i + 1];
		i++;
	}
	return (ligne);
}

char	**split_var(t_minishell *minishell)
{
	char	*res;
	char	**split;

	res = get_env("PATH", minishell->env);
	split = ft_split(res, ':', 0);
	free(res);
	return (split);
}

int	parse_redi_word(char *ligne, int *j, int *i)
{
	int		incr;
	char	quote;

	incr = 0;
	while (ligne[(*j)] && ligne[(*j)] != ' ')
	{
		if (ligne[(*j)] == '\'' || ligne[(*j)] == '"')
		{
			(*i)++;
			quote = ligne[(*j)++];
			while (ligne[*j] && ligne[*j] != quote)
				(*j)++;
			incr = 1;
		}
		(*j)++;
	}
	return (incr);
}
