/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 00:59:26 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/15 01:12:05 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_redir	*new_redir(t_type type, char *file)
{
	t_redir	*new;

	new = ft_calloc(1, sizeof(t_redir));
	if (!new)
		return (NULL);
	new->type = type;
	new->file = file;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_redir	*get_last_redir(t_redir *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

t_redir	*append_redir(t_redir **head, t_redir *new)
{
	t_redir	*last;

	if (!(*head))
		*head = new;
	else
	{
		last = get_last_redir(*head);
		last->next = new;
		new->prev = last;
	}
	return (new);
}
