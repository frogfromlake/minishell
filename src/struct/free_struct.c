/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:30:58 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/07 23:01:03 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_node(t_node **node)
{
	t_node	*curr;
	t_node	*next;

	curr = *node;
	while (curr)
	{
		next = curr->next;
		if (curr->tokens)
			free_token(&curr->tokens);
		free(curr);
		curr = next;
	}
	*node = NULL;
	node = NULL;
}

void	free_token(t_token **token)
{
	t_token	*curr;
	t_token	*next;

	curr = *token;
	while (curr)
	{
		next = curr->next;
		free(curr->name);
		curr->name = NULL;
		free(curr);
		curr = next;
	}
	*token = NULL;
	token = NULL;
}

void	free_table(t_table **table) // TODO: free redirs
{
	t_table	*curr;
	t_table	*next;

	curr = *table;
	while (curr)
	{
		next = curr->next;
		if (curr->cmd_arr)
			ft_free_array(curr->cmd_arr, false, false); // FIXME: doesn't work properly
		if (curr->exe)
			free(curr->exe);
		if (curr->args)
			free(curr->args);
		free(curr);
		curr = next;
	}
	*table = NULL;
	table = NULL;
}