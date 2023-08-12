/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:22:52 by elisa             #+#    #+#             */
/*   Updated: 2023/08/12 16:22:46 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_alone(int fd, char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		write(fd, "declare -x ", 11);
		while (tab[i][j])
		{
			if (tab[i][j] == '=')
			{
				write(fd, &tab[i][j], 1);
				j++;
				write(fd, "\"", 1);
			}
			write(fd, &tab[i][j], 1);
			j++;
		}
		write(1, "\"", 1);
		write(fd, "\n", 1);
		i++;
	}
}

int	add_var_env(char *word, char *value, t_minishell *minishell)
{
	char	**var;
	int		i;

	minishell->size_env += 1;
	var = malloc(sizeof (char *) * (minishell->size_env + 1));
	i = 0;
	while (minishell->env[i])
	{
		var[i] = ft_strdup(minishell->env[i]);
		i++;
	}
	var[i] = set_value(word, value);
	var[++i] = NULL;
	minishell->env = var;
	return (1);
}

void	export_by_ascii(char **tab, int size_env)
{
	int		order;
	int		i;
	char	*tmp;

	order = 0;
	while (tab && order == 0)
	{
		order = 1;
		i = 0;
		while (i < size_env - 1)
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				order = 0;
			}
			i++;
		}
		size_env--;
	}
}

void	aff_export_alone(int fd, t_minishell *minishell)
{
	char	**tab;

	tab = copy_tab(minishell->env);
	export_by_ascii(tab, minishell->size_env);
	export_alone(fd, tab);
}

void	export(t_command *c, t_minishell *minishell)
{
	int	k;
	int	i;

	i = 0;
	if (!c->option[0])
		aff_export_alone(c->fd_out, minishell);
	else
	{
		k = 0;
		while (c->option[i] && c->option[i][k] && c->option[i][k] != '=')
		{
			if (check_option_export(c, minishell, i, k) == 0)
				return ;
		}
		if (c->option[i][k] == '\0')
			add_var_env(ft_strdup(c->option[i]), NULL, minishell);
		else
			add_var_env(get_char(c->option[i], 0, k),
				c->option[i] + k + 1, minishell);
		minishell->status = 0;
		i++;
	}
}
