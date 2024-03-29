/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:08:50 by cmichez           #+#    #+#             */
/*   Updated: 2023/09/03 15:54:12 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**parse_quote(char **ligne, t_minishell *minishell)
{
	int		i;
	char	*tmp;

	i = 0;
	while (ligne[i])
	{
		tmp = ft_strdup(ligne[i]);
		free(ligne[i]);
		ligne[i] = display_quote(tmp, minishell);
		free(tmp);
		i++;
	}
	return (ligne);
}

char	*display_quote(char *ligne, t_minishell *minishell)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_strdup("");
	while (ligne[i])
	{
		if (ligne[i] == '\'' && is_inquote(ligne, i) != 2)
			i++;
		else if (ligne[i] == '"' && is_inquote(ligne, i) != 1)
			i++;
		else if (ligne[i] == '$' && ligne[i + 1] != '"' && ligne[i + 1] != '\''
			&& ligne[i + 1] && ligne[i + 1] != ' ' && is_inquote(ligne, i) != 1
			&& ligne[i - 1] != '\\')
		{
			i++;
			res = ft_strjoin_free(res, var_env(ligne + i, minishell));
			i += var_size(ligne + i);
		}
		else
			res = replace_quote(res, ligne[i++]);
	}
	return (res);
}

char	*replace_quote(char *str, char c)
{
	int		i;
	char	*new;

	i = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) + 2));
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	free(str);
	new[i] = c;
	new[i + 1] = 0;
	return (new);
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
	return (ft_strdup(""));
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
