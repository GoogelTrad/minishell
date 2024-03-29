/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:07:53 by elisa             #+#    #+#             */
/*   Updated: 2023/09/02 14:05:55 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_option_echo(char	*str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i] == 'n')
		i++;
	if (str[i] != ' ' && str[i] != '\0')
		return (0);
	return (1);
}

void	ft_putstr(char *s)
{
	int	a;

	a = 0;
	while (s[a] != '\0')
	{
		ft_putchar(s[a]);
		a++;
	}
}

int	ft_isalnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!((48 <= str[i] && 57 >= str[i]) || (65 <= str[i] && 90 >= str[i])
				|| (97 <= str[i] && 122 >= str[i])))
			return (0);
		i++;
	}
	return (1);
}

int	overflow(int element)
{
	if (element < 0)
		return (0);
	return (-1);
}

int	ft_atoi(const char *str)
{
	int	element;
	int	nbr;
	int	i;

	element = 1;
	nbr = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		element *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if ((nbr * 10 + (str[i] - '0')) / 10 != nbr)
			return (overflow(element));
		nbr *= 10;
		nbr += str[i] - '0';
		i++;
	}
	return (element * nbr);
}
