/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelix <nelix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 18:58:22 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/03 04:00:36 by nelix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*new_token(char *input, t_type type)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->name = input;
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_token	*get_last_token(t_token *head)
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
