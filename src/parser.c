/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelix <nelix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:24:41 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/03 04:00:16 by nelix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parser(t_node **node, t_table **table)
{
	// t_table	*help;
	// t_table	*new;

	// help = *table;
	// new = NULL;
	create_cmd_table(node, table);
	return (0);
}

void	create_cmd_table(t_node **node, t_table **table)
{
	t_node	*curr_n;
	t_table	*new;

	curr_n = *node;
	while (curr_n)
	{
		new = append_table(table, new_table());
		if (check_log_op(curr_n->type))
		{
			new->log_op = curr_n->type;
			curr_n = curr_n->next;
			continue ;
		}
		while (curr_n && !check_log_op(curr_n->type))
		{
			if (check_redir(curr_n->type))
				redir_parser(curr_n->tokens, &new);
			if (curr_n->type == COMMAND)
			{
				new->exe = ft_strdup(curr_n->tokens->name);
				if (!ft_strcmp(new->exe, "echo"))
				{
					if (curr_n->tokens->next)
						echo_parser(curr_n->tokens->next, &new);
				}
				else if (curr_n->tokens->next)
					new->args = ft_strdup(curr_n->tokens->next->name);
			}
			curr_n = curr_n->next;
		}
	}
}
