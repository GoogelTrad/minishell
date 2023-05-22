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

void double_droite(void)
{
    int fd;
	char *ligne;
    char *readed;
	int i;

	i = 0;
    fd = open(g_minishell.command->redi->word, O_CREAT | O_RDWR);
    if (!fd)
        printf("Probleme lors de l'ouverture du fichier !\n");
    ligne = malloc(1);
    ligne = "\0";
	while (g_minishell.command->option[i])
	{
		ligne = ft_strjoin(ligne, g_minishell.command->option[i]);
        if (ligne[i + 1])
		    ligne = ft_strjoin(ligne, " ");
		i++;
	}
    readed = NULL;
    while(read(fd, readed, 1));
    if (ft_strlen(readed))
    {
        //supprimer + reecrire dessus
    }
	close(fd);
}