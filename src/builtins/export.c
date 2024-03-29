/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:22:52 by elisa             #+#    #+#             */
/*   Updated: 2023/09/03 11:40:00 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_alone(int fd, char **tab)
{
	int	i;
	int	j;
	int	eg;

	i = -1;
	while (tab[++i])
	{
		j = 0;
		write(fd, "declare -x ", 11);
		eg = 0;
		while (tab[i][j])
		{
			if (tab[i][j] == '=')
			{
				eg = 1;
				j++;
				write(fd, "=\"", 2);
			}
			write(fd, &tab[i][j], 1);
			j++;
		}
		if (eg)
			write(fd, "\"", 1);
		write(fd, "\n", 1);
	}
}

int	add_var_env(char *word, char *value, t_minishell *minishell)
{
	char	**var;
	int		i;
	int		index;

	index = find_my_var(word, minishell);
	if (index != -1)
		return (change_var(word, value, index, minishell));
	var = malloc(sizeof (char *) * (minishell->size_env + 2));
	i = 0;
	while (minishell->env[i])
	{
		var[i] = ft_strdup(minishell->env[i]);
		i++;
	}
	free_double_tab(minishell->env);
	var[i] = set_value(word, value);
	var[++i] = NULL;
	minishell->env = var;
	minishell->size_env += 1;
	return (1);
}

void	export_by_ascii(char **tab)
{
	int		i;
	int		j;
	int		size;
	char	*tmp;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[j])
		{
			size = ft_strlen(tab[i]);
			if (size < ft_strlen(tab[j]))
				size = ft_strlen(tab[j]);
			if (ft_strncmp(tab[i], tab[j], size) < 0)
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

void	export_opt(t_command *c, t_minishell *minishell)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (c->option[i])
	{
		k = 0;
		if (c->option[i][0] == '=')
		{
			error_arg(c, &i);
			return ;
		}
		if (check_option_export(c, i, &k) == 0)
			return ;
		if (c->option[i][k] == '\0')
			add_var_env(ft_strdup(c->option[i]), NULL, minishell);
		else
			add_var_env(get_char(c->option[i], 0, k),
				c->option[i] + k + 1, minishell);
		g_status = 0;
		i++;
	}
}

void	export(t_command *c, t_minishell *minishell)
{
	int	i;

	i = 0;
	if (!c->option[0])
		aff_export_alone(c->fd_out, minishell);
	else if (c->option[0][0] == '=')
		error_arg(c, &i);
	else
		export_opt(c, minishell);
}
