/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:22:16 by cmichez           #+#    #+#             */
/*   Updated: 2023/07/02 00:11:52 by cmichez          ###   ########.fr       */
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
			g_minishell.ligne = ft_strdup(ligne);
			ligne = var_env(ligne, g_minishell.env);
			separate_cmd(ligne);
			belle_exec(g_minishell.command);
		}
	}
    return 0;
}