/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:45:30 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/11 21:38:55 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	executer(t_table **table)
{
	int		childs;
	int		here_doc;
	t_table	*tmp;

	childs = 0;
	tmp = *table;
	here_doc = 0;
	while (tmp)
	{
		if (!check_log_op(tmp->log_op))
			childs++;
		while (tmp->redir_in)
		{
			if (*(int *)(tmp->redir_in->content) == LESSLESS)
				here_doc++;
			tmp->redir_in = tmp->redir_in->next;
		}
		tmp = tmp->next;
	}
	create_child_prcs(table, childs);
}

void	create_child_prcs(t_table **table, int childs)
{
	int		i;
	pid_t	pid;
	t_table	*tmp;
	int		tmp_fd_in;
	int		fd[2];
	int		exit_status;

	i = 0;
	tmp_fd_in = dup(STDIN_FILENO);
	pipe(fd);
	tmp = *table;
	while (tmp && i < childs)
	{
		if (tmp->log_op != COMMAND)
			tmp = tmp->next;
		pid = fork();
		if (pid < 0)
			perror("Could not fork.");
		if (pid == 0)
		{
			child_prc(childs, i, tmp, fd, tmp_fd_in);
		}
		close(fd[1]);
		close(tmp_fd_in);
		dup2(fd[0], tmp_fd_in);
		close(fd[0]);
		i++;
		tmp = tmp->next;
	}
	while (i != -1)
		i = waitpid(0, &exit_status, 0);
}

void	child_prc(int childs, int i, t_table *table, int fd[2], int tmp_fd_in)
{
	char	**env_arr;

	(void)childs;
	env_arr = get_env_arr();
	if (i == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (!built_in_exec(table) && table->cmd_arr[0])
			execve(table->cmd_arr[0], table->cmd_arr, env_arr);
	}
	else
	{
		close(fd[0]);
		dup2(tmp_fd_in, STDIN_FILENO);
		close(fd[1]);
		if (!built_in_exec(table) && table->cmd_arr[0])
			execve(table->cmd_arr[0], table->cmd_arr, env_arr);
	}
}
