/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:24:41 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/02 03:53:00 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_node **node, t_table **table)
{
	t_table	*help;
	t_table	*new;

	help = *table;
	new = NULL;
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
		if (curr_n->type == PIPE)
		{
			curr_n = curr_n->next;
			continue ;
		}
		new = append_table(table, new_table());
		while (curr_n && curr_n->type != PIPE)
		{
			if (check_redir(curr_n->type))
			{
				if (curr_n->type == LESS || curr_n->type == LESSLESS)
				{
					if (new->redir_in)
						new->redir_in = str_join(new->redir_in, " ", curr_n->tokens->name);
					else
						new->redir_in = ft_strdup(curr_n->tokens->name);
				}
				else
				{
					if (new->redir_out)
						new->redir_out = str_join(new->redir_out, " ", curr_n->tokens->name);
					else
						new->redir_out = ft_strdup(curr_n->tokens->name);
				}
			}
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
