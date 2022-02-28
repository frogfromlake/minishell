/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:24:41 by dmontema          #+#    #+#             */
/*   Updated: 2022/02/28 22:02:37 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_node **node, t_table **table)
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
				{
					new->redir_in = str_join(new->redir_in, "< ", help->tokens->name);
				}
				else
				{
					new->redir_in = str_join("< ", help->tokens->name, " ");
					printf("%s\n", new->redir_in);
				}
			}
			if (help->type == GREAT)
			{
				if (new->redir_out)
				{
					new->redir_out = str_join(new->redir_out, "> ", help->tokens->name);
				}
				else
				{
					new->redir_out = str_join("> ", help->tokens->name, " ");
					printf("%s\n", new->redir_out);
				}
			}
			if (help->type == LESSLESS)
			{
				if (new->redir_in)
				{
					new->redir_in = str_join(new->redir_in, "<< ", help->tokens->name);
				}
				else
				{
					new->redir_in = str_join("<< ", help->tokens->name, " ");
					printf("%s\n", new->redir_in);
				}
			}
			if (help->type == GREATGREAT)
			{
				if (new->redir_out)
				{
					new->redir_out = str_join(new->redir_out, ">> ", help->tokens->name);
				}
				else
				{
					new->redir_in = str_join(">> ", help->tokens->name, " ");
					printf("%s\n", new->redir_out);
				}
			}
			else if (help->type == COMMAND)
			{
				if (!help->tokens->next)
				{
					new->exe = help->tokens->name;
					printf("%s\n", new->exe);
				}
				else if (!help->tokens->next->next)
				{
					new->exe = help->tokens->name;
					printf("%s\n", new->exe);
					new->args = help->tokens->next->name;
					printf("%s\n", new->args);
				}
				else if (help->tokens->next->next)
				{
					new->exe = help->tokens->name;
					printf("%s\n", new->exe);
					new->args = ft_strjoin(help->tokens->next->name, " ");
					new->args = ft_strjoin(new->args, help->tokens->next->next->name);
					printf("%s\n", new->args);
				}
			}
			help = help->next;
		}
	}
	return (0);
}
