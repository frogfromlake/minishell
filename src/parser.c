/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:24:41 by dmontema          #+#    #+#             */
/*   Updated: 2022/02/28 18:01:43 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parser(t_node **node, t_table **table)
{
	t_node	*help;
	t_table	*new;

	help = *node;
	while (help)
	{
		if (help->type == PIPE)
		{
			help = help->next;
			continue;
		}
		new = append_table(table, new_table());
		while (help->type != PIPE)
		{
			if (help->type == LESS)
				new->redir_in = help->args;
			else if (help->type == GREAT)
				new->redir_out = help->args;
		}
	}
}