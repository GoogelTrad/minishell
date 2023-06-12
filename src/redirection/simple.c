/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:02:29 by cmichez           #+#    #+#             */
/*   Updated: 2023/06/12 18:33:44 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_minishell g_minishell;

void simple_droite(t_command *c)
{
    c->fd_out = open(c->redi->word, O_CREAT | O_RDWR | O_TRUNC, 0644);
}

void simple_gauche(t_command *c)
{
	c->fd_out = open(c->redi->word, O_RDONLY);
}
