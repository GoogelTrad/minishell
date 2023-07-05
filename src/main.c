/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:22:16 by cmichez           #+#    #+#             */
/*   Updated: 2023/07/06 00:46:58 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell g_minishell;

int	main(int ac, char **av, char **env)
{
	char	*ligne;
	
	(void)ac;
	g_minishell.env = copy_env(env);
	signal(SIGINT, &get_sigint);
	g_minishell.av = copy_env(av);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
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
	(void)signal;
	printf("Quit : 3\n");
	rl_replace_line("", 0);
	rl_redisplay();
}

void bworded(t_command *c)
{
	if (ft_strcmp(c->cmd, "cat") == 0 && c->option[0] == NULL)
		signal(SIGQUIT, &blocksig);
}

char *var_arg(char **av, char *ligne)
{
	char *res;
	char *tmp;
	int i;
	int nb;

	i = 0;
	while (ligne[i])
	{
		if (ligne[i] == '$' && ft_isdigit(ligne[i + 1]))
		{
			tmp = ft_strndup(ligne, i - 1);
			nb = ligne[i + 1] - '0';
			if (av[nb])
				res = ft_strdup(av[nb]);
			else
				res = "";
			tmp = ft_strjoin(tmp, res);
			ligne = ft_strjoin(tmp, ligne + i + 2);
		}
		i++;
	}
	return (ligne);
}