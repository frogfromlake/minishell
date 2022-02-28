/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 18:59:54 by dmontema          #+#    #+#             */
/*   Updated: 2022/02/28 18:13:16 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*new_node()
{
	t_node	*new;

	new = ft_calloc(1, sizeof(t_node));
	if (!new)
		return (NULL);
	new->args = NULL;
	new->here_doc = NULL;
	new->cmdpath = NULL;
	new->cmd_arr = NULL;
	new->in = PIPEIN;
	new->out = PIPEOUT;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_node	*get_last_node(t_node *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

t_node	*append_node(t_node **head, t_node *new)
{
	t_node	*last;

	if (!(*head))
		*head = new;
	else
	{
		last = get_last_node(*head);
		last->next = new;
		new->prev = last;
	}
	return (new);
}

// Commandtable

t_table	*new_element(void)
{
	t_table	*new;

	new = ft_calloc(1, sizeof(t_table));
	if (!new)
		return (NULL);
	new->exe = NULL;
	new->args = NULL;
	new->redir_in = NULL;
	new->redir_out = NULL;
	return (new);
}

t_table	*get_last_element(t_table *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

t_table	*append_element(t_table **head, t_table *new)
{
	t_table	*last;

	if (!(*head))
		*head = new;
	else
	{
		last = get_last_element(*head);
		last->next = new;
		new->prev = last;
	}
	return (new);
}
