/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:08:50 by cmichez           #+#    #+#             */
/*   Updated: 2023/07/31 20:22:05 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_minishell g_minishell;

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
				k = ++j;
				quote = str[i][j - 1];
				while (str[i][j] && str[i][j] != quote && str[i][j - 1] != '\\')
					j++;
				if (str[i][j] == quote)
				{
					str[i] = replace(str[i], k - 1, j + 1);
					j = -1;
				}
			}
			j++;
		}
		i++;
	}
	return (str);
}

char *replace(char *str, int start, int end)
{
	int i;
	
	i = 0;
	if (str[start] == str[start + 1])
		end = start;
	while (i < start && start)
		i++;
	start = -1;
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
	i = 0;
	while (i < end && end)
		i++;
	end = -1;
	if (!str[i])
		str[i - 2] = 0;
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
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