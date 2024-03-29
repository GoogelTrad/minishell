/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 01:51:01 by cmichez           #+#    #+#             */
/*   Updated: 2023/05/22 01:51:01 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	double_droite(t_command *c)
{
	c->fd_out = open(c->redi->word, O_CREAT | O_RDWR | O_APPEND, 0644);
	return (1);
}

int	double_gauche(t_command *c, t_minishell *minishell)
{
	int		pipes[2];
	char	*ligne;

	pipe(pipes);
	c->fd_in = pipes[0];
	double_check_env(minishell, c);
	ligne = readline("> ");
	impr_double(c, pipes, ligne);
	while (ft_strcmp(ligne, c->redi->word) != 0)
	{
		free(ligne);
		ligne = readline("> ");
		impr_double(c, pipes, ligne);
	}
	free(ligne);
	close(pipes[1]);
	return (1);
}

char	*coucou(char *ligne)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	while (ligne[i])
	{
		if (ligne[i] == '$')
		{
			j = i;
			while (ligne[i] && ligne[i] != ' ' && ligne[i] != '"'
				&& ligne[i] != '\'')
				i++;
			res = ft_strndup(ligne + j, i);
			printf("res = %s\n", res);
			return (res);
		}
		i++;
	}
	return (NULL);
}

int	check_env(char *ligne)
{
	int	i;

	i = 0;
	while (ligne[i])
	{
		if (ligne[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	impr_double(t_command *c, int pipes[2], char *ligne)
{
	int	i;

	i = 0;
	if (ft_strcmp(ligne, c->redi->word) != 0)
	{
		while (ligne[i])
			write(pipes[1], &ligne[i++], 1);
		write(pipes[1], "\n", 1);
	}
}
