/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:08:50 by cmichez           #+#    #+#             */
/*   Updated: 2023/09/01 12:55:34 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**parse_quote(char **ligne, t_minishell *minishell)
{
	int	i;

	i = 0;
	while (ligne[i])
	{
		ligne[i] = display_quote(ligne[i], minishell);
		i++;
	}
	return (ligne);
}

char	*display_quote(char *ligne, t_minishell *minishell)
{
	int	i;
	char	*res;

	i = 0;
	res = ft_strdup("");
	while (ligne[i])
	{
		if (ligne[i] == '\'' && is_inquote(ligne, i) != 2)
			i++;
		else if (ligne[i] == '"' && is_inquote(ligne, i) != 1)
			i++;
		else if (ligne[i] == '$' && ligne[i + 1] != '"' && ligne[i + 1] != '\'' &&
			ligne[i + 1] && ligne[i + 1] != ' ' && is_inquote(ligne, i) != 1)
		{
			i++;
			res = ft_strjoin_free(res, var_env(ligne + i, minishell));
			i += var_size(ligne + i);
		}
		else
		{
			res = replace_quote(res, ligne[i]);
			i++;
		}
	}
	return (res);
}

/*
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
					str[i[0]] = replace(str[i[0]], quote);
			}
			i[1]++;
		}
		i[0]++;
	}
	return (str);
}
*/

char	*replace_quote(char *str, char c)
{
	int		i;
	char	*new;

	i = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) + 2));
	new =  ft_strdup(str);
	free(str);
	while (new[i])
		i++;
	new[i] = c;
	new[i + 1] = 0;
	return (new);
}

/*
char	*replace(char *str, char quote)
{
	int	i;

	i = 0;
	printf("str = %s\n", str);
	while (str[i] != quote)
		i++;
	str = replace_quote(str, i);
	i = 0;
	while (str[i] != quote)
		i++;
	str = replace_quote(str, i);
	printf("str = %s\n", str);
	//while(1);
	return (str);
}
*/
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
