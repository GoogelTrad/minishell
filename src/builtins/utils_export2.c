/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:21:37 by elisa             #+#    #+#             */
/*   Updated: 2023/08/19 20:54:42 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid(int c)
{
	if (((65 <= c && 90 >= c) || (97 <= c && 122 >= c)) && (c >= 48 && c <= 57))
		return (1);
	return (0);
}

int	isok(t_command *c, t_minishell *minishell, int i, int k)
{
	if (!is_valid(c->option[i][k]))
	{
		if (c->option[i][k] == '&' || c->option[i][k] == ';'
			|| c->option[i][k] == '|')
		{
			printf("%s: '%s': command not found\n",
				c->cmd, c->option[i]);
			minishell->status = 1;
		}
		else if (c->option[i][k] == '(' || c->option[i][k] == ')')
		{
			printf("%s: '%s': syntax error near unexpected token '%c'\n",
				c->cmd, c->option[i], c->option[i][k]);
			minishell->status = 1;
		}
		else
		{
			printf("%s: '%s': not a valid identifier\n",
				c->cmd, c->option[i]);
			minishell->status = 1;
		}
		return (0);
	}
	else
		return (1);
}

int	check_option_export(t_command *c, t_minishell *minishell, int i, int *k)
{
	int	x;

	x = 0;
	while (c->option[i] && c->option[i][*k] && c->option[i][*k] != '=')
	{
		if (ft_isalpha(c->option[i][*k]))
		{
			x = 1;
			(*k)++;
		}
		else if ((c->option[i][*k] == '_'
			|| ft_isdigit(c->option[i][*k])) && x == 1)
			(*k)++;
		else
			return (isok(c, minishell, i, *k));
	}
	return (1);
}

int	find_my_var(char *word, t_minishell *minishell)
{
	int		j;
	int		k;
	char	*stock2;

	k = 0;
	stock2 = malloc(sizeof(char) * 100);
	while (minishell->env[k])
	{
		j = 0;
		while (minishell->env[k][j] && minishell->env[k][j] != '=')
		{
			stock2[j] = minishell->env[k][j];
			j++;
		}
		stock2[j] = '\0';
		if (ft_strcmp(stock2, word) == 0)
		{
			free(stock2);
			return (k);
		}
		k++;
	}
	free(stock2);
	return (-1);
}

int	change_var(char *word, char *value, int index, t_minishell *minishell)
{
	free(minishell->env[index]);
	minishell->env[index] = set_value(word, value);
	return (1);
}
