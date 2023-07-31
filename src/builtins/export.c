/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:22:52 by elisa             #+#    #+#             */
/*   Updated: 2023/07/24 17:15:56 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_minishell g_minishell;

void	export_alone(int fd, char **tab)
{
	int i;
	int j;

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

void		export_by_ascii(char **tab, int size_env)
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

int	add_var_env(char *word, char *value)
{
	char	**var;
	int		i;

	g_minishell.size_env += 1;
	var = malloc(sizeof (char *) * (g_minishell.size_env + 1));
	i = 0;
	while (g_minishell.env[i])
	{
		var[i] = ft_strdup(g_minishell.env[i]);
		i++;
	}
	var[i] = set_value(word, value);
	var[++i] = NULL;
	g_minishell.env = var;
	return (1);
}

void	aff_export_alone(int fd)
{
	char	**tab;

	tab = copy_tab(g_minishell.env);
	export_by_ascii(tab, g_minishell.size_env);
	export_alone(fd, tab);
}

int	ft_valid_arg(char *str)
{
	int	x;
	int	i;

	x = 0;
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (ft_isalpha(str[i]))
		{
			x = 1;
			i++;
		}
		else if (ft_isdigit(str[i]) && x == 1)
			i++;
		else
			return (0);
	}
	return (1);
}

void	export(t_command *c)
{
	int k;
	int i;

	i = 0;
	if (!c->option[0])
		aff_export_alone(c->fd_out);
    else
    {
		while (c->option[i])
		{
			k = 0;
			while (c->option[i][k] && c->option[i][k] != '=')
			{
				if (!(ft_valid_arg(c->option[i])))
				{
					printf("%s: '%s': not a valid identifier\n",
					c->cmd, c->option[i]);
					g_minishell.status = 1;
					return ;
				}
				k++;
			}
			if (c->option[i][k] == '\0')
				add_var_env(ft_strdup(c->option[i]), NULL);
			else
				add_var_env(get_char(c->option[i], 0, k), c->option[i] + k + 1);
			g_minishell.status = 0;
			i++;
		}
	}
}
