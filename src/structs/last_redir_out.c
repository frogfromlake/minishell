/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_redir_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelix <nelix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 23:30:34 by fquist            #+#    #+#             */
/*   Updated: 2022/04/02 00:53:28 by nelix            ###   ########.fr       */
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
	{
		g_exit_status = 1;
		return (-1);
	}
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
			{
				if (route_append(head, out) < 0)
					break ;
			}
		}
		head = head->next;
	}
	return (out);
}
