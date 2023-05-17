/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:07:53 by elisa             #+#    #+#             */
/*   Updated: 2023/05/17 12:23:44 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_option_echo(char	*str)
{
	int	i;

	i = 0;
	while (str[i] == 'n')
		i++;
	if (str[i] != ' ' && str[i] != '\0')
		return (0);
	return (1);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
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

int	ft_isalnum(int c)
{
	if ((48 <= c && 57 >= c) || (65 <= c && 90 >= c) || (97 <= c && 122 >= c))
		return (1);
	return (0);
}

void	overflow(void)
{
	write(2, "Error\n", 7);
	exit(0);
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
			overflow();
		nbr *= 10;
		nbr += str[i] - '0';
		i++;
	}
	return (element * nbr);
}