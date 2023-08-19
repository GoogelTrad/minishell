/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 20:46:59 by elisa             #+#    #+#             */
/*   Updated: 2023/08/19 20:57:41 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_pipe(t_minishell *minishell)
{
	write(2, "syntax error near unexpected token 'newline'\n", 45);
	minishell->status = 1;
}
