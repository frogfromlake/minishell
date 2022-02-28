/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:00:22 by dmontema          #+#    #+#             */
/*   Updated: 2022/02/28 18:28:38 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_table	*new_table()
{
	t_table	*new;

	new = ft_calloc(1, sizeof(t_table));
	if (!new)
		return (NULL);
	new->exec = NULL;
	new->tokens = NULL;
	new->redir_in = NULL;
	new->redir_out = NULL;
	new->redir_out = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_table	*get_last_table(t_table *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

t_table	*append_table(t_table **head, t_table *new)
{
	t_table	*last;

	if (!(*head))
		*head = new;
	else
	{
		last = get_last_table(*head);
		last->next = new;
		new->prev = last;
	}
	return (new);
}
