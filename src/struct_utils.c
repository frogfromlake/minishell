/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:56:58 by fquist            #+#    #+#             */
/*   Updated: 2022/02/26 19:16:08 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_nodes(t_node *node)
{
	while (node)
	{
		printf("Type: %d\n", node->type);
		if (node->args)
			print_tokens(node->args);
		node = node->next;
	}
}

void	print_tokens(t_token *token)
{
	while (token)
	{
		printf("Cmd: %s\n", token->cmd);
		token = token->next;
	}
}

void	free_list(t_node **lst, bool exit, bool exit_status)
{
	t_node	*current;
	t_node	*next;

	current = *lst;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*lst = NULL;
	lst = NULL;
	if (exit == true && exit_status == false)
		ft_exit_print(exit_status, "Error\n", 2);
	else if (exit == true && exit_status == true)
		ft_exit_print(exit_status, "Error\n", 2);
}
