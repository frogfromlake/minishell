/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 03:09:51 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/02 03:10:32 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_echo_opt_valid(char *opt)
{
	int	i;

	i = 1;
	while (opt[i])
	{
		if (opt[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int echo_parser(t_token *help, t_table **new)
{
	bool	echo_opt_valid;

	echo_opt_valid = is_echo_opt_valid(help->name);
	if (echo_opt_valid)
	{
		(*new)->args = ft_strdup("-n");
		help = help->next;
		while (help)
		{
			if (!ft_strcmp(help->name, "-n"))
			{
				help = help->next;
				continue ;
			}
			else
				break ;
		}
		while (help)
		{
			(*new)->args = str_join((*new)->args, " ", help->name);
			help = help->next;
		}
	}
	else
	{
		(*new)->args = ft_strdup(help->name);
		help = help->next;
		while (help)
		{
			(*new)->args = str_join((*new)->args, " ", help->name);
			help = help->next;
		}
	}
	return (1);
}
