/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:41:46 by cmichez           #+#    #+#             */
/*   Updated: 2023/08/06 17:38:00 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_command(int verif, t_command *c, t_minishell *minishell)
{
	if (!verif)
	{
		minishell->status = 127;
		write(2, c->cmd, ft_strlen(c->cmd));
		write(2, ": ", 2);
		write(1, "command not found\n", 18);
	}
}

void	fusion_exec(t_command *c, t_minishell *minishell)
{
	int	i;

	i = 0;
	while (c->option[i])
		i++;
	minishell->fusion = malloc(sizeof(char *) + (i + 1));
	i = 0;
	minishell->fusion[0] = ft_strdup(c->cmd);
	while (c->option[i])
	{
		minishell->fusion[i + 1] = ft_strdup(c->option[i]);
		i++;
	}
	minishell->fusion[i + 1] = NULL;
}

void	free_double_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*str;
	long	nb;

	i = count_size(n);
	nb = n;
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (0);
	if (n < 0)
		nb *= -1;
	str[i--] = '\0';
	while (i >= 0)
	{
		str[i] = nb % 10 + 48;
		nb /= 10;
		i--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

void	char_split(char *str, int *i, char sep, char quote)
{
	while (char_is_sep(str[*i], sep) && str[*i] && quote == ' ')
		(*i)++;
}
