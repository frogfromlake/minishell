/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 20:02:17 by fquist            #+#    #+#             */
/*   Updated: 2022/03/15 22:56:49 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_exec	*new_exec(void)
{
	t_exec	*new;

	new = ft_calloc(1, sizeof(t_exec));
	if (!new)
		return (NULL);
	new->fd[READ] = 0;
	new->fd[WRITE] = 0;
	new->here_fd[READ] = 0;
	new->here_fd[WRITE] = 0;
	new->stin = dup(STDIN_FILENO);
	new->stout = dup(STDOUT_FILENO);
	new->tmp_fd = dup(STDIN_FILENO);
	new->file_fd = 0;
	new->cmd_count = 0;
	new->no_rights = 0;
	return (new);
}