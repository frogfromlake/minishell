/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:32:58 by fquist            #+#    #+#             */
/*   Updated: 2022/04/06 15:34:05 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_nodes(t_node *node)
{
	while (node)
	{
		printf("%sNODE%s\n", CYAN, RESET);
		printf("Type: %d\n", node->type);
		if (node->tokens)
			print_tokens(node->tokens);
		printf("%s--------%s\n", CYAN, RESET);
		node = node->next;
	}
}

void	print_tokens(t_token *token)
{
	while (token)
	{
		printf("%sTOKEN%s\n", PURPLE, RESET);
		printf("Name: %s\n", token->name);
		printf("Type: %d\n", token->type);
		printf("%s------%s\n", PURPLE, RESET);
		token = token->next;
	}
}

void	print_cmd_table(t_table *table)
{
	t_redir	*tmp;
	int		i;

	if (!table)
		printf("EMPTY!!!\n");
	while (table)
	{
		i = 0;
		printf("----------\n");
		printf("CMD_ARR: ");
		while (table->cmd_arr[i])
			printf("%s ", table->cmd_arr[i++]);
		printf("%s ", table->cmd_arr[i]);
		printf("\n");
		printf("EXE: %s\n", table->exe);
		printf("OPT: %d\n", table->opt);
		printf("LOG_OP: %d\n", table->log_op);
		printf("REDIR: ");
		if (table->redir)
		{
			tmp = table->redir;
			while (tmp)
			{
				printf("[%d %s] ", tmp->type, tmp->file);
				tmp = tmp->next;
			}
			tmp = table->redir;
			if (get_last_in_redir(tmp) || get_last_out_redir(tmp))
			{
				printf("|");
				if (get_last_in_redir(tmp))
					printf(" [LAST IN: %s] ", get_last_in_redir(tmp)->file);
				if (get_last_out_redir(tmp))
					printf(" [LAST OUT: %s]", get_last_out_redir(tmp)->file);
			}
		}
		printf("\n");
		printf("----------\n");
		table = table->next;
	}
}
