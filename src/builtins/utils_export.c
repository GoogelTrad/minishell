/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichez <cmichez@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:17:35 by elisa             #+#    #+#             */
/*   Updated: 2023/08/03 16:41:12 by cmichez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**copy_tab(char **tab)
{
	char	**copy_tab;
	int	i;

	i = 0;
	while (tab[i])
		i++;
	copy_tab = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (tab[i])
	{
		copy_tab[i] = ft_strdup(tab[i]);
		i++;
	}
	copy_tab[i] = NULL;
	return (copy_tab);
}

int	ft_isalpha(int c)
{
	if ((65 <= c && 90 >= c) || (97 <= c && 122 >= c))
		return (1);
	return (0);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count != 0)
		if (SIZE_MAX / count <= size)
			return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

char	*get_char(char *cmd, size_t start, size_t end)
{
	size_t	i;
	size_t	j;
	char	*first;

	if (end <= start)
		return (NULL);
	first = ft_calloc(1, end - start + 1);
	if (!first)
		return (NULL);
	i = start;
	j = 0;
	while (i < end)
		first[j++] = cmd[i++];
	first[j] = '\0';
	return (first);
}

char	*set_value(char *word, char *value)
{
	char	*var;
	int		size_word;
	int		size_value;
	int		i;
	int		j;

	size_word = ft_strlen(word);
	size_value = ft_strlen(value);
	var = malloc(sizeof (char) * ((size_value + 1)+ (size_word + 1)));
	i = -1;
	j = -1;
	while (++i < size_word)
		var[i] = word[i];
	if (value != 0)
	{
		var[i] = '=';
		while (++j < size_value)
			var[++i] = value[j];
	}
	var[++i] = '\0';
	if (word)
		free(word);
	return (var);
}
