/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:22:52 by elisa             #+#    #+#             */
/*   Updated: 2023/08/13 16:37:55 by acolin           ###   ########.fr       */
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
	// si la variable exite
	// modifier la variable avec le bon kw
	// if (find_my_var(kw, t_minishell *minishell))
	// 	return (modif_my_var(kw, value, t_minishell *minishell));
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
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < size_env - 1)
	{
		j = 0;
		while (j < size_env - 1)
		{
			if (ft_strncmp(tab[i], tab[j], ft_strlen(tab[i])) < 0)
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
			j++;
		}
		i++;
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
	int	i;
	int k;

	i = 0;
	if (!c->option[0])
		aff_export_alone(c->fd_out, minishell);
	else
	{
		while (c->option[i]) 
		{
			k = 0;
			if (check_option_export(c, minishell, i, &k) == 0)
				return ;
			if (c->option[i][k] == '\0')
				add_var_env(ft_strdup(c->option[i]), NULL, minishell);
			else
				add_var_env(get_char(c->option[i], 0, k),
					c->option[i] + k + 1, minishell);
			minishell->status = 0;
			i++;
		}
	}
}
