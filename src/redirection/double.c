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

void double_droite(void (*cmd)(int))
{
    g_minishell.fd = open(g_minishell.command->redi->word, O_CREAT | O_RDWR | O_APPEND | O_TRUNC);
    if (!g_minishell.fd)
        printf("Probleme lors de l'ouverture du fichier !\n");
    (*cmd)(g_minishell.fd);
	close(g_minishell.fd);
}