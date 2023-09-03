/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 12:14:18 by elisa             #+#    #+#             */
/*   Updated: 2023/09/03 22:57:23 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	err_(t_command *c)
{
	ft_putstr("exit\n");
	printf("minishell: exit: %s: numeric argument required\n", c->option[0]);
	exit(2);
}

void	err_nb_arg(void)
{
	ft_putstr("exit\n");
	printf("minishell: exit: too many arguments\n");
	exit(1);
}
