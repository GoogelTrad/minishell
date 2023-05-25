/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:02:29 by cmichez           #+#    #+#             */
/*   Updated: 2023/05/25 03:15:46 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_minishell g_minishell;

void simple_droite(void (*cmd)(int))
{
   	g_minishell.fd = open(g_minishell.command[g_minishell.num].redi->word, O_CREAT | O_RDWR);
    if (!g_minishell.fd)
        printf("Probleme lors de l'ouverture du fichier !\n");
	(*cmd)(g_minishell.fd);
	close(g_minishell.fd);
}