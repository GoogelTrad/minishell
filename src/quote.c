/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epraduro <epraduro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:53:05 by cmichez           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/07/10 17:27:47 by epraduro         ###   ########.fr       */
=======
/*   Updated: 2023/07/10 17:24:48 by cmichez          ###   ########.fr       */
>>>>>>> bb1999effc759303a39a8d4a7cb6585d2dc8e3ba
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words_quote(char *str, char sep)
{
	int		i;
	char	quote;
	int		nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		while (char_is_sep(str[i], sep))
			i++;
		if (!(char_is_sep(str[i], sep)) && str[i])
			nb++;
		while (!(char_is_sep(str[i], sep)) && str[i])
		{
			if (str[i] == '"' || str[i] == '\'')
			{
				quote = str[i];
				i++;
				while (str[i] && str[i] != quote)
					i++;
				i++;
			}
			else
				i++;
		}
	}
	return (nb);
}

char	**separate_quote(char *str, char sep)
{
<<<<<<< HEAD
	char	**res;
	char	quote;
	int		i;
	int		j;
	int		n;
	//int limite[2];
=======
	char **res;
	char quote;
	int	i;
	int	j;
	int n;

>>>>>>> bb1999effc759303a39a8d4a7cb6585d2dc8e3ba
	i = 0;
	n = 0;
	res = malloc(sizeof(char *) * (count_words_quote(str, sep) + 1));
	while (str[i])
	{
		while (str[i] && char_is_sep(str[i], sep))
			i++;
		j = i;
		while (!char_is_sep(str[i], sep) && str[i])
		{
			if ((str[i] == '"' || str[i] == '\'') && str[i - 1] != '\\')
			{
				quote = str[i];
				i++;
				while (str[i] && str[i] != quote && str[i - 1] != '\\')
					i++;
				i++;
			}
			else
				i++;
		}
		res[n++] = ft_strndup(str + j, i - j);
		while (char_is_sep(str[i], sep) && str[i])
			i++;
	}
	res[n] = 0;
	return (res);
}

<<<<<<< HEAD
/*
char	**separate_quote(char *str, char sep)
=======
char *dolar_dolar(void)
>>>>>>> bb1999effc759303a39a8d4a7cb6585d2dc8e3ba
{
	pid_t pid;
	char *res;

	pid = getpid();
	printf("coucou\n");
	res = ft_itoa(pid);
	printf("res = %s\n", res);
	return (res);
}