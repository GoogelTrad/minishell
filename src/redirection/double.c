/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 01:51:01 by cmichez           #+#    #+#             */
/*   Updated: 2023/05/22 01:51:01 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_minishell g_minishell;

void double_droite(t_command *c)
{
    c->fd_out = open(c->redi->word, O_CREAT | O_RDWR | O_APPEND, 0644);
}

void double_gauche(t_command *c)
{
    int pipes[2];
    char *ligne;
    int i;

    pipe(pipes);
    c->fd_in = pipes[0];
    if (check_env(g_minishell.ligne))
        c->redi->word = ft_strdup(coucou(g_minishell.ligne));
    do
    {
        i = 0;
        ligne = readline("> ");
        if(ft_strcmp(ligne, c->redi->word) != 0)
        {
            while(ligne[i])
                write(pipes[1], &ligne[i++], 1);
            write(pipes[1], "\n", 1);
        }
    } while (ft_strcmp(ligne, c->redi->word) != 0);
    close(pipes[1]);
    
}

char *coucou(char *ligne)
{
    int i;
    int j;
    char *res;

    i = 0;
    j = 0;
    while (ligne[i])
    {
        if (ligne[i] == '$')
        {
            j = i;
            while(ligne[i] && ligne[i] != ' ')
                i++;
            res = ft_strndup(ligne + j, i);
            return (res);
        }
        i++;
    }
    return (NULL);
}

int check_env(char *ligne)
{
    int i;

    i = 0;
    while (ligne[i])
    {
        if (ligne[i] == '$')
            return (1);
        i++;
    }
    return (0);
}

