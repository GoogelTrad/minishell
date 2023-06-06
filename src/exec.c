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
    else
        exec_others();
    g_minishell.num++;
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

void    exec_others(void)
{
    char **path;
    char *fusion;
    int i;

    i = 0;
    if (open(g_minishell.command[g_minishell.num].cmd, O_RDONLY) > -1)
        exec_fork(g_minishell.command[g_minishell.num].cmd);
    else
    {
        path = ft_split(var_env("$PATH", g_minishell.env), ':');
        while (path[i])
        {
            fusion = ft_strjoin(path[i], "/");
            fusion = ft_strjoin(fusion, g_minishell.command[g_minishell.num].cmd);
            if (open(fusion, O_RDONLY) > -1)
            {
                exec_fork(fusion);
                break ;
            }
            i++;
        }
    }
    //free path
}

void exec_fork(char *fichier)
{
    int pid;
    int status;

    pid = fork();
    fusion_exec();
    if (pid == 0)
    {
        execve(fichier, g_minishell.fusion, g_minishell.env);
        exit(0);
    }
    else
        waitpid(pid, &status, 0);
}

void fusion_exec()
{
    int i;

    i = 0;
    while (g_minishell.command[g_minishell.num].option[i])
        i++;
    g_minishell.fusion = malloc(sizeof(char *) + (i + 2));
    i = 0;
    g_minishell.fusion[0] = g_minishell.command[g_minishell.num].cmd;
    while (g_minishell.command[g_minishell.num].option[i])
    {
        g_minishell.fusion[i + 1] = ft_strdup(g_minishell.command[g_minishell.num].option[i]);
        i++;
    }
    g_minishell.fusion[i + 1] = NULL;
}