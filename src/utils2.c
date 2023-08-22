/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 20:46:59 by elisa             #+#    #+#             */
/*   Updated: 2023/08/22 11:42:38 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void end_pipe(void)
{
	write(2, "syntax error near unexpected token 'newline'\n", 45);
	g_status = 1;
}
