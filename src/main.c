/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:22:16 by cmichez           #+#    #+#             */
/*   Updated: 2023/08/29 21:07:24 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

int	main(int ac, char **av, char **env)
{
	char		*ligne;
	t_minishell	minishell;

	minishell.av = copy_env(av);
	minishell.size_env = len_env(env);
	init_env(env, &minishell);
	minishell.ac = ac;
	minishell.incr = 0;
	while (1)
	{
		signal(SIGINT, &get_sigint);
		signal(SIGQUIT, SIG_IGN);
		ligne = readline("MiniShell> ");
		if (ligne == NULL)
		{
			printf("exit\n");
			free_all(&minishell);
			free(ligne);
			exit(g_status);
		}
		if (ligne[0])
			prompt(ligne, &minishell);
		free(ligne);
	}
	return (0);
}

void	prompt(char *ligne, t_minishell *minishell)
{
	add_history(ligne);
	minishell->ligne = ft_strdup(ligne);
	ligne = var_env(ligne, 0, minishell);
	if (separate_cmd(ligne, minishell))
	{
		bworded(minishell->command);
		belle_exec(minishell->command, minishell);
		free_cmd(minishell);
	}
}

void	get_sigint(int signal)
{
	(void)signal;
	g_status = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	blocksig(int signal)
{
	(void)signal;
	g_status = 131;
	printf("Quit : 3\n");
	rl_replace_line("", 0);
	rl_redisplay();
}

char	*var_arg(char **av, char *ligne, int ac)
{
	char	*res;
	char	*tmp;
	char	*temp;
	int		i;
	int		nb;

	i = 0;
	while (ligne[i])
	{
		if (ligne[i] == '$' && ft_isdigit(ligne[i + 1]))
		{
			temp = ft_strndup(ligne, i - 1);
			nb = ligne[i + 1] - '0';
			if (nb <= ac && av[nb])
				res = ft_strdup(av[nb]);
			else
				res = "";
			tmp = ft_strjoin(temp, res);
			ligne = ft_strjoin(tmp, ligne + i + 2);
			free(tmp);
			free(temp);
		}
		i++;
	}
	return (ligne);
}
