/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route_stdout.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 14:26:17 by fquist            #+#    #+#             */
/*   Updated: 2022/03/27 15:14:34 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	route_stdout(t_table *table, t_exec *fds)
{
	t_redir	*last_out;

	last_out = get_last_out_redir(table->redir);
	if (last_out)
		last_redir_out(fds, last_out);
	else
		handle_redir_out(table, fds);
}

void	last_redir_out(t_exec *fds, t_redir *last_out)
{
	if (last_out->type == GREAT)
	{
		fds->file_fd = open_file(last_out->file,
				O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fds->file_fd < 0)
			return ;
		dup2(fds->file_fd, STDOUT_FILENO);
		close(fds->file_fd);
	}
	if (last_out->type == GREATGREAT)
	{
		fds->file_fd = open_file(last_out->file,
				O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fds->file_fd < 0)
			return ;
		dup2(fds->file_fd, STDOUT_FILENO);
		close(fds->file_fd);
	}
}

void	handle_redir_out(t_table *table, t_exec *fds)
{
	{
		if (table->next == NULL)
		{
			if (fds->here_fd[READ] > 0 || fds->here_fd[WRITE] > 0)
			{
				dup2(fds->stout, fds->here_fd[WRITE]);
				close(fds->stout);
			}
			dup2(fds->stout, STDOUT_FILENO);
			close(fds->stout);
		}
		else
		{
			if (fds->here_fd[READ] > 0 || fds->here_fd[WRITE] > 0)
			{
				dup2(fds->fd[READ], fds->here_fd[WRITE]);
				close(fds->fd[READ]);
			}
			dup2(fds->fd[WRITE], STDOUT_FILENO);
			close(fds->fd[WRITE]);
		}
	}
}
