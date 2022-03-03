/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelix <nelix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 17:01:26 by fquist            #+#    #+#             */
/*   Updated: 2022/03/03 05:25:17 by nelix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	executer(t_table **table)
{
	// **table
	int		status;
	int		childs;
	int		here_doc;
	pid_t	*pids;

	while (table)
	{
		if (ft_strcmp((*table)->redir_in, "<<"))
			here_doc = 1;
		childs++;
		*table = (*table)->next;
	}
	pids = create_child_prcs(childs, table, here_doc);
	status = child_wait_pid(pids, childs);
	free(pids);
	exit(status);
}
