/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:22:16 by cmichez           #+#    #+#             */
/*   Updated: 2023/07/03 20:12:08 by cmichez          ###   ########.fr       */
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
			affiche(g_minishell.command);
			bworded(g_minishell.command);
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

void blocksig(int signal)
{
	printf("Quit : 3");
	get_sigint(signal);
}

void bworded(t_command *c)
{
	if (ft_strcmp(c->cmd, "cat") == 0 && c->option[0] == NULL)
		signal(SIGQUIT, &blocksig);
	else
		signal(SIGQUIT, SIG_IGN);
}