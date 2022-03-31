/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route_stdin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 14:24:55 by fquist            #+#    #+#             */
/*   Updated: 2022/03/31 21:05:47 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	last_route(t_redir *last_in, t_exec *fds)
{
	if (last_in->type == LESS)
	{
		fds->file_fd = open_file(last_in->file, O_RDONLY, 0);
		if (fds->file_fd < 0)
			return (-1);
		dup2(fds->file_fd, STDIN_FILENO);
		close(fds->file_fd);
	}
	else if (last_in->type == LESSLESS || last_in->type == LESSLESS + 1)
	{
		pipe(fds->here_fd);
		heredoc(last_in->file, fds, last_in->type);
		dup2(fds->here_fd[READ], STDIN_FILENO);
	}
	return (0);
}

int	route_stdin(t_table *table, t_exec *fds)
{
	t_redir	*last_in;

	last_in = get_last_in_redir(table->redir);
	if (multiple_redir_in(table, fds) < 0)
		return (-1);
	if (last_in)
	{
		if (last_route(last_in, fds) < 0)
			return (-1);
	}
	else if (!last_in)
	{
		dup2(fds->tmp_fd, STDIN_FILENO);
		close(fds->tmp_fd);
	}
	return (0);
}

static void	route_heredoc(t_exec *fds, t_redir *tmp)
{
	pipe(fds->here_fd);
	heredoc(tmp->file, fds, tmp->type);
	dup2(fds->here_fd[WRITE], STDOUT_FILENO);
	close(fds->here_fd[WRITE]);
}

int	multiple_redir_in(t_table *table, t_exec *fds)
{
	t_redir	*tmp;

	tmp = table->redir;
	if (table->redir && table->redir->next && (table->redir->next->type == LESS
			|| table->redir->next->type == LESSLESS
			|| table->redir->next->type == LESSLESS + 1))
	{
		while (tmp)
		{
			if (tmp->next && (tmp->type == LESS || tmp->type == LESSLESS
					|| tmp->type == LESSLESS + 1))
			{
				if (tmp->type == LESS)
				{
					fds->file_fd = open_file(tmp->file, O_RDONLY, 0);
					if (fds->file_fd < 0)
						return (-1);
				}
				if (tmp->type == LESSLESS)
					route_heredoc(fds, tmp);
			}
			tmp = tmp->next;
		}
	}
	return (0);
}
