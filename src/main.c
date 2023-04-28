/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:22:16 by cmichez           #+#    #+#             */
/*   Updated: 2023/04/28 15:00:27 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell g_minishell;

int	main(int ac, char **av, char **env)
{
	t_command	*command;
	char		*ligne;
	
	(void)av;
	(void)ac;
	g_minishell.env = copy_env(env);
	while(1)
	{
		ligne = readline("MiniShell> ");
		if (ligne[0])
			add_history(ligne);
		ligne = var_env(ligne, g_minishell.env);
		command = separate_cmd(ligne);
	}
	(void)command;
    return 0;
}