/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 00:49:06 by cmichez           #+#    #+#             */
/*   Updated: 2023/04/28 00:49:06 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	int		len_s1;
	int		n;
	int		i;
	int		len_s2;
	
	n = 0;
	i = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (!(malloc(sizeof(char) * (len_s1 + len_s2) + 1)))
		return (NULL);
	else
		result = malloc(sizeof(char) * (len_s1 + len_s2) + 1);

	while(n < len_s1)
	{
		result[n] = s1[n];
		n++;
	}
	while (n < (len_s1 + len_s2))
		result[n++] = s2[i++];
	result[n] = 0;
	return (result);
}