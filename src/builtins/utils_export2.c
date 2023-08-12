/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:21:37 by elisa             #+#    #+#             */
/*   Updated: 2023/08/12 17:26:10 by acolin           ###   ########.fr       */
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
		{	
			(*k)++;
		}
		else 
		{
			if (isok(c, minishell, i, *k) == 0)
				return (0);
			else
				return (1);
		}
	}
	return (1);
}
