/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:00:22 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/09 22:58:57 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_table	*new_table(void)
{
	t_table	*new;

	new = ft_calloc(1, sizeof(t_table));
	if (!new)
		return (NULL);
	new->exe = NULL;
	new->args = NULL;
	new->log_op = 0;
	new->redir = NULL;
	new->opt = 0;
	new->cmd_arr = ft_calloc(2, sizeof(char *));
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
