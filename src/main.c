/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:22:16 by cmichez           #+#    #+#             */
/*   Updated: 2023/08/03 16:32:33 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*ligne;

	t_minishell minishell;

	minishell.av = copy_env(av);
	minishell.size_env = len_env(env);
	init_env(env, &minishell);
	signal(SIGINT, &get_sigint);
	minishell.ac = ac;
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		ligne = readline("MiniShell> ");
		if (ligne == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		if (ligne[0])
			prompt(ligne, &minishell);
	}
	return (0);
}

void	prompt(char *ligne, t_minishell *minishell)
{
	add_history(ligne);
	minishell->ligne = ft_strdup(ligne);
	ligne = var_env(ligne, 0, minishell);
	separate_cmd(ligne, minishell);
	bworded(minishell->command);
	belle_exec(minishell->command, minishell);
}

void	get_sigint(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	blocksig(int signal)
{
	(void)signal;
	printf("Quit : 3\n");
	rl_replace_line("", 0);
	rl_redisplay();
}

char	*var_arg(char **av, char *ligne, int ac)
{
	char	*res;
	char	*tmp;
	int		i;
	int		nb;

	i = 0;
	while (ligne[i])
	{
		if (ligne[i] == '$' && ft_isdigit(ligne[i + 1]))
		{
			tmp = ft_strndup(ligne, i - 1);
			nb = ligne[i + 1] - '0';
			if (nb <= ac)
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
