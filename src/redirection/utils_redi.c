/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:08:50 by cmichez           #+#    #+#             */
/*   Updated: 2023/08/03 16:16:20 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void parse_redi(char **ligne, t_command *c)
{
	int i;
	t_redirection *tmp;

	i = 0;
	while (ligne[i] && ligne[i][0] != '>' && ligne[i][0] != '<')
		i++;
	c->option = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (ligne[i] && ligne[i][0] != '>' && ligne[i][0] != '<')
	{
		c->option[i] = ft_strdup(ligne[i]);
		i++;
	}
	c->option[i] = NULL;
	tmp = c->redi;
	while (ligne [i])
	{
		c->redi->type = ft_strdup(ligne[i]);
		c->redi->there = 1;
		i++;
		if (ligne[i])
		{
			c->redi->word = ft_strdup(ligne[i]);
			if(ligne[i + 1])
			{
				c->redi->next_redi = malloc(sizeof(t_redirection));
				c->redi = c->redi->next_redi;
				c->redi->there = 0;
			}
		}
		i++;
	}
	c->redi->next_redi = malloc(sizeof(t_redirection));
	c->redi->next_redi->there = 0;
	c->redi = tmp;
}

char **display_quote(char **str)
{
	char quote;
	int i;
	int j;
	int k;
	
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if ((str[i][j] == '"' || str[i][j] == '\'') && str[i][j - 1] != '\\')
			{
				k = j++;
				quote = str[i][k];
				while (str[i][j] && str[i][j] != quote)
					j++;
				if (str[i][j] == quote && j != k)
				{
					str[i] = replace(str[i], quote);
					j = -1;
				}
			}
			j++;
		}
		i++;
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

char	*replace(char *str, char quote)
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
	return (str);
}

char	*get_env(char *var, char **env)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen((var));
	while(env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0)
			return (ft_strdup(env[i] + len + 1));
		i++;
	}
	return (NULL);
}