/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:22:16 by cmichez           #+#    #+#             */
/*   Updated: 2023/05/17 14:58:38 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell g_minishell;

int	main(int ac, char **av, char **env)
{
	char		*ligne;
	
	(void)av;
	(void)ac;
	g_minishell.env = copy_env(env);
	while(1)
	{
		ligne = readline("MiniShell> ");
		if (ligne[0])
		{
			add_history(ligne);
			ligne = var_env(ligne, g_minishell.env);
			g_minishell.command = separate_cmd(ligne);
			printf("ligne = %s\n", ligne);
			exec();
		}
	}
    return 0;
}