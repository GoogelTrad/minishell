/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 17:45:54 by cmichez           #+#    #+#             */
/*   Updated: 2023/07/02 20:19:17 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell g_minishell;

void get_signal(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
	{
		printf("coucou\n");
		exit(1);
	}
}

void set_signal_action(void)
{
	struct sigaction sig_int;
	struct sigaction sig_quit;

	ft_bzero(&sig_int, sizeof(sig_int));
	ft_bzero(&sig_quit, sizeof(sig_quit));
	sig_int.sa_handler = &get_signal;
	sigaction(SIGINT, &sig_int, NULL);
	sig_quit.sa_handler = &get_signal;
	sigaction(SIGQUIT, &sig_quit, NULL);
}