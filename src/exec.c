/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:51:59 by cmichez           #+#    #+#             */
/*   Updated: 2023/05/05 15:51:59 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell g_minishell;

void exec(void)
{
    if (ft_strcmp(g_minishell.command->cmd, "echo") == 0)
        echo();
    if (ft_strcmp(g_minishell.command->cmd, "exit") == 0)
        ft_exit();
    if (ft_strcmp(g_minishell.command->cmd, "pwd") == 0)
        pwd();
}