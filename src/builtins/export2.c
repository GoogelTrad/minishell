/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:47:53 by elisa             #+#    #+#             */
/*   Updated: 2023/09/03 11:40:05 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_arg(t_command *c, int *i)
{
	printf("%s: '%s': not a valid identifier\n",
		c->cmd, c->option[*i]);
	g_status = 1;
}

void	aff_export_alone(int fd, t_minishell *minishell)
{
	char	**tab;

	tab = copy_tab(minishell->env);
	export_by_ascii(tab);
	export_alone(fd, tab);
	free_double_tab(tab);
}
