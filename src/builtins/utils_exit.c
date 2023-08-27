/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 12:14:18 by elisa             #+#    #+#             */
/*   Updated: 2023/08/23 12:14:59 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	err_(t_command *c)
{
	ft_putstr("exit\n");
	printf("minishell: exit: %s: numeric argument required\n", c->option[0]);
	exit(255);
}

void	err_nb_arg(void)
{
	ft_putstr("exit\n");
	printf("minishell: exit: too many arguments\n");
	exit(1);
}
