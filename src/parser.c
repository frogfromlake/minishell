/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:24:41 by dmontema          #+#    #+#             */
/*   Updated: 2022/02/28 23:46:24 by fquist           ###   ########.fr       */
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
	// while (help)
	// {
		
	// 	help = help->next;
	// }
	return (0);
}

void	create_cmd_table(t_node **node, t_table **table)
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
		while (help && help->type != PIPE)
		{
			if (help->type == LESS)
			{
				if (new->redir_in)
					new->redir_in = str_join(new->redir_in, "< ", help->tokens->name);
				else
					new->redir_in = str_join("< ", help->tokens->name, " ");
			}
			if (help->type == GREAT)
			{
				if (new->redir_out)
					new->redir_out = str_join(new->redir_out, "> ", help->tokens->name);
				else
					new->redir_out = str_join("> ", help->tokens->name, " ");
			}
			if (help->type == LESSLESS)
			{
				if (new->redir_in)
					new->redir_in = str_join(new->redir_in, "<< ", help->tokens->name);
				else
					new->redir_in = str_join("<< ", help->tokens->name, " ");
			}
			if (help->type == GREATGREAT)
			{
				if (new->redir_out)
					new->redir_out = str_join(new->redir_out, ">> ", help->tokens->name);
				else
					new->redir_in = str_join(">> ", help->tokens->name, " ");
			}
			else if (help->type == COMMAND)
			{
				if (!help->tokens->next)
					new->exe = help->tokens->name;
				else if (!help->tokens->next->next)
				{
					new->exe = help->tokens->name;
					new->args = help->tokens->next->name;
				}
				else if (help->tokens->next->next)
				{
					new->exe = help->tokens->name;
					new->args = ft_strjoin(help->tokens->next->name, " ");
					new->args = ft_strjoin(new->args, help->tokens->next->next->name);
				}
			}
			help = help->next;
		}
	}
}
