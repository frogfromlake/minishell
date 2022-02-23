/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:56:58 by fquist            #+#    #+#             */
/*   Updated: 2022/02/23 18:30:45 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *input)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->cmd = input;
	new->type = COMMAND;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

static t_token	*get_last_token(t_token *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

t_token	*append_token(t_token **head, t_token *new)
{
	t_token	*last;

	if (!(*head))
		*head = new;
	else
	{
		last = get_last_token(*head);
		last->next = new;
		new->prev = last;
	}
	return (new);
}
