/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_redir_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 23:30:34 by fquist            #+#    #+#             */
/*   Updated: 2022/04/04 15:35:00 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	route_append(t_redir *out)
{
	open(out->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (access(out->file, W_OK) < 0)
		return (-1);
	return (0);
}

int	route_out(t_redir *out)
{
	open(out->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (access(out->file, W_OK) < 0)
		return (-1);
	return (0);
}

t_redir	*get_last_out_redir(t_redir *head)
{
	t_redir	*out;

	out = NULL;
	while (head)
	{
		if (head->type == GREAT || head->type == GREATGREAT)
		{
			out = head;
			if (head->type == GREAT)
			{
				if (route_out(out) < 0)
					break ;
			}
			else if (head->type == GREATGREAT)
			{
				if (route_append(out) < 0)
					break ;
			}
		}
		head = head->next;
	}
	return (out);
}
