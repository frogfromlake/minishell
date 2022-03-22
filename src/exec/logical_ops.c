/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 22:18:38 by fquist            #+#    #+#             */
/*   Updated: 2022/03/20 00:23:52 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	operation_logic(t_table *table, t_exec *fds)
{
	if (table->log_op == AND)
	{
		table = table->next;
		close(fds->stin);
		close(fds->stout);
		close(fds->tmp_fd);
		while (fds->i > 0)
		{
			waitpid(0, &fds->pid, 0);
			if (WIFEXITED(fds->pid))
				fds->exit_status = WEXITSTATUS(fds->pid);
			fds->i--;
		}
		if (access(table->exe, F_OK))
			exec_loop(table);
		else
			return (fds->exit_status);
	}
	return (fds->exit_status);
}
