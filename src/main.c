/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:22:16 by cmichez           #+#    #+#             */
/*   Updated: 2023/04/27 14:51:42 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_command	*command;
	char		*ligne;
	
	(void) ac, av;
	while(1)
	{
		ligne = readline("MiniShell> ");
		ligne = var_env(ligne, env);
		command = separate_cmd(ligne);
		if (ligne[0])
			add_history(ligne);
	}
	(void)command;
    return 0;
}