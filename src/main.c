/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:22:16 by cmichez           #+#    #+#             */
/*   Updated: 2023/07/03 16:56:25 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell g_minishell;

int	main(int ac, char **av, char **env)
{
	char	*ligne;
	
	(void)av;
	(void)ac;
	g_minishell.env = copy_env(env);
	signal(SIGINT, &get_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		ligne = readline("MiniShell> ");
		if(ligne == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		if (ligne[0])
		{
			add_history(ligne);
			g_minishell.ligne = ft_strdup(ligne);
			ligne = var_env(ligne, g_minishell.env);
			separate_cmd(ligne);
			belle_exec(g_minishell.command);
		}
	}
    return (0);
}

void get_sigint(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}