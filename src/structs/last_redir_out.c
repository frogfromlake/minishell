/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_redir_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 23:30:34 by fquist            #+#    #+#             */
/*   Updated: 2022/03/31 02:07:54 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	route_append(int current_file, t_redir *head, t_redir *out)
{
	if (head->next)
	{
		head = head->next;
		return (g_exit_status);
	}
	current_file = open_file(out->file,
			O_RDWR | O_CREAT | O_APPEND, 0644);
	if (current_file == -1)
	{
		g_exit_status = 1;
		return (g_exit_status);
	}
	return (g_exit_status);
}

t_redir	*get_last_out_redir(t_redir *head)
{
	t_redir	*out;
	int		current_file;

	out = NULL;
	while (head)
	{
		if (head->type == GREAT || head->type == GREATGREAT)
		{
			out = head;
			if (head->type == GREAT)
			{
				current_file = open_file(out->file,
						O_RDWR | O_CREAT | O_TRUNC, 0644);
				if (current_file == -1)
				{
					g_exit_status = 1;
					break ;
				}
			}
			else if (head->type == GREATGREAT)
				route_append(current_file, head, out);
		}
		head = head->next;
	}
	return (out);
}
