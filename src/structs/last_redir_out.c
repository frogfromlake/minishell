/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_redir_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 23:30:34 by fquist            #+#    #+#             */
/*   Updated: 2022/03/31 18:42:35 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	route_append(t_redir *head, t_redir *out)
{
	if (head->next)
	{
		head = head->next;
		return (g_exit_status);
	}
	if (access(out->file, W_OK) < 0)
		g_exit_status = 1;
	return (g_exit_status);
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
				if (access(out->file, W_OK) < 0)
				{
					g_exit_status = 1;
					break ;
				}
			}
			else if (head->type == GREATGREAT)
				route_append(head, out);
		}
		head = head->next;
	}
	return (out);
}
