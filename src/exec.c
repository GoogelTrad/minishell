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

void exec(int fd)
{
    if (ft_strcmp(g_minishell.command[g_minishell.num].cmd, "echo") == 0)
        echo(fd);
    else if (ft_strcmp(g_minishell.command[g_minishell.num].cmd, "exit") == 0)
        ft_exit();
    else if (ft_strcmp(g_minishell.command[g_minishell.num].cmd, "pwd") == 0)
        pwd(fd);
    else if (ft_strcmp(g_minishell.command[g_minishell.num].cmd, "env") == 0)
        env(fd);
}

void exec_redi(void)
{
    if(g_minishell.command[g_minishell.num].redi->there)
    {
        if (ft_strcmp(g_minishell.command[g_minishell.num].redi->type, ">") == 0)
            simple_droite(&exec);
        else if (ft_strcmp(g_minishell.command[g_minishell.num].redi->type, ">>") == 0)
            double_droite(&exec);
        else if (ft_strcmp(g_minishell.command[g_minishell.num].redi->type, "<") == 0)
            printf("coucou\n");
        else if (ft_strcmp(g_minishell.command[g_minishell.num].redi->type, "<<") == 0)
            printf("Coucou\n");
    }
    else
        exec(1);
}