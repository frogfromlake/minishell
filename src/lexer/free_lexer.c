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
	*node = 0;
	node = 0;
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
		curr->name = 0;
		free(curr);
		curr = next;
	}
	*token = 0;
	token = 0;
}
