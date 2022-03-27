/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 00:59:26 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/27 00:20:30 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

t_redir	*get_last_in_redir(t_redir *head)
{
	t_redir	*in;

	if (!head)
		return (NULL);
	in = NULL;
	while (head)
	{
		if (head->type == LESS || head->type == LESSLESS
			|| head->type == LESSLESS + 1)
			in = head;
		head = head->next;
	}
	return (in);
}

t_redir	*get_last_out_redir(t_redir *head)
{
	t_redir	*out;
	int		current_file;

	if (!head)
		return (NULL);
	out = NULL;
	while (head)
	{
		if (head->type == GREAT || head->type == GREATGREAT)
		{
			out = head;
			if (head->type == GREAT)
			{
				current_file = open_file(out->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
				if (current_file == -1)
					exit(1);
			}
			else if (head->type == GREATGREAT)
			{
				if(head->next)
				{
					head = head->next;
					continue ;
				}
				current_file = open_file(out->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
				if (current_file == -1)
					exit(1);
			}
		}
		head = head->next;
	}
	return (out);
}
