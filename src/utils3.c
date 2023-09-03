/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:33:33 by elisa             #+#    #+#             */
/*   Updated: 2023/09/03 11:59:16 by elisa            ###   ########.fr       */
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
