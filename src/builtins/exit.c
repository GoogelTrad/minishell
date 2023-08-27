/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:36:39 by elisa             #+#    #+#             */
/*   Updated: 2023/08/23 12:14:48 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_atoi_exit(const char *str)
{
	int				element;
	long long int	nbr;
	int				i;

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

static int	check_arg(char *arg)
{
	int	i;
	int	nb;
	int	space;

	i = 0;
	nb = 0;
	space = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == 0 && arg[i] != ' ' && arg[i] != '\f'
			&& arg[i] != '\t' && arg[i] != '\r' && arg[i] != '\v')
			return (-1);
		if (ft_isdigit(arg[i]) == 1)
			nb = 1;
		if (arg[i] == ' ' && nb == 1)
			space = 1;
		if (ft_isdigit(arg[i]) == 1 && space == 1)
			return (-1);
		i++;
	}
	return (0);
}

void	exit_nb(int nb)
{
	ft_putstr("exit\n");
	exit(nb);
}

void	oui(t_command *c, int nb)
{
	nb = nb % 256;
	if (nb <= 0 && ft_strlen(c->option[0]) > 20)
		err_(c);
	else
		exit_nb(nb);
}

void	ft_exit(t_command *c, t_minishell *minishell)
{
	long long int	nb;
	long long int	i;

	nb = 0;
	i = 0;
	while (c->option[i])
		i++;
	if (i == 1)
	{
		if (check_arg(c->option[0]) == -1)
			err_(c);
		else
		{
			nb = ft_atoi_exit(c->option[0]);
			oui(c, nb);
		}
	}
	else if (i >= 2)
		err_nb_arg();
	else
		ft_putstr("exit\n");
	free_all(minishell);
	exit(g_status);
}
