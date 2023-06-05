/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:02:29 by cmichez           #+#    #+#             */
/*   Updated: 2023/06/05 18:53:36 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_minishell g_minishell;

void simple_droite(void (*cmd)(int))
{
   	g_minishell.fd = open(g_minishell.command[g_minishell.num].redi->word, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (g_minishell.fd == 0)
		printf("Il y a eu un probleme lors de l'ouverture du fichier.\n");
	(*cmd)(g_minishell.fd);
	close(g_minishell.fd);
}

void simple_gauche(void (*cmd)(int))
{
	g_minishell.fd = open(g_minishell.command[g_minishell.num].redi->word, O_RDONLY);
	if (g_minishell.fd == 0)
		printf("Il y a eu un probleme lors de l'ouverture du fichier.\n");
	(*cmd)(g_minishell.fd);	
	close(g_minishell.fd);
}
