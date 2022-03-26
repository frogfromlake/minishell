/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route_stdin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 14:24:55 by fquist            #+#    #+#             */
/*   Updated: 2022/03/26 14:25:36 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	route_stdin(t_table *table, t_exec *fds)
{
	t_redir	*last_in;

	last_in = get_last_in_redir(table->redir);
	multiple_redir_in(table, fds);
	if (last_in)
	{
		if (last_in->type == LESS)
		{
			fds->file_fd = open_file(last_in->file, O_RDONLY, 0);
			dup2(fds->file_fd, STDIN_FILENO);
			close(fds->file_fd);
		}
		else if (last_in->type == LESSLESS || last_in->type == LESSLESS + 1)
		{
			pipe(fds->here_fd);
			heredoc(last_in->file, fds, last_in->type);
			dup2(fds->here_fd[READ], STDIN_FILENO);
		}
	}
	else
	{
		dup2(fds->tmp_fd, STDIN_FILENO);
		close(fds->tmp_fd);
	}
}

void	multiple_redir_in(t_table *table, t_exec *fds)
{
	t_redir	*tmp;

	tmp = table->redir;
	if (table->redir && table->redir->next)
	{
		while (tmp)
		{
			if (tmp->next && (tmp->type == LESS || tmp->type == LESSLESS
					|| tmp->type == LESSLESS + 1))
			{
				if (tmp->type == LESS)
					fds->file_fd = open_file(tmp->file, O_RDONLY, 0);
				if (tmp->type == LESSLESS)
				{
					pipe(fds->here_fd);
					heredoc(tmp->file, fds, tmp->type);
					dup2(fds->here_fd[WRITE], STDOUT_FILENO);
					close(fds->here_fd[WRITE]);
				}
			}
			tmp = tmp->next;
		}
	}
}