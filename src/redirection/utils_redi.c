/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:08:50 by cmichez           #+#    #+#             */
/*   Updated: 2023/08/22 20:40:10 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**display_quote(char **str)
{
	char	quote;
	int		i[2];
	int		k;

	i[0] = 0;
	while (str[i[0]])
	{
		i[1] = 0;
		while (str[i[0]][i[1]])
		{
			if ((str[i[0]][i[1]] == '"' || str[i[0]][i[1]] == '\'') &&
				str[i[0]][i[1] - 1] != '\\')
			{
				k = i[1]++;
				quote = str[i[0]][k];
				while (str[i[0]][i[1]] && str[i[0]][i[1]] != quote)
					i[1]++;
				if (str[i[0]][i[1]] == quote && i[1] != k)
					str[i[0]] = replace(str[i[0]], quote, &i[1]);
			}
			i[1]++;
		}
		i[0]++;
	}
	return (str);
}

char	*replace_quote(char *str, int i)
{
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
	return (str);
}

char	*replace(char *str, char quote, int *j)
{
	int	i;

	i = 0;
	while (str[i] != quote)
		i++;
	str = replace_quote(str, i);
	i = 0;
	while (str[i] != quote)
		i++;
	str = replace_quote(str, i);
	(*j) = -1;
	return (str);
}

char	*get_env(char *var, char **env)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen((var));
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0)
			return (ft_strdup(env[i] + len + 1));
		i++;
	}
	return (NULL);
}

void	double_check_env(t_minishell *minishell, t_command *c)
{
	char	*tmp;
	
	if (check_env(minishell->ligne))
	{
		tmp = coucou(minishell->ligne);
		c->redi->word = ft_strdup(tmp);
		free(tmp);
	}
}	